#include <time.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#define WHITE 0xFFFF
#define PUSHBUTTONS ((volatile long *)0xFF200050)
/* This files provides address values that exist in the system */

#define BOARD                 "DE1-SoC"

/* Memory */
#define DDR_BASE              0x00000000
#define DDR_END               0x3FFFFFFF
#define A9_ONCHIP_BASE        0xFFFF0000
#define A9_ONCHIP_END         0xFFFFFFFF
#define SDRAM_BASE            0xC0000000
#define SDRAM_END             0xC3FFFFFF
#define FPGA_ONCHIP_BASE      0xC8000000
#define FPGA_ONCHIP_END       0xC803FFFF
#define FPGA_CHAR_BASE        0xC9000000
#define FPGA_CHAR_END         0xC9001FFF

/* Cyclone V FPGA devices */
#define LEDR_BASE             0xFF200000
#define HEX3_HEX0_BASE        0xFF200020
#define HEX5_HEX4_BASE        0xFF200030
#define SW_BASE               0xFF200040
#define KEY_BASE              0xFF200050
#define JP1_BASE              0xFF200060
#define JP2_BASE              0xFF200070
#define PS2_BASE              0xFF200100
#define PS2_DUAL_BASE         0xFF200108
#define JTAG_UART_BASE        0xFF201000
#define JTAG_UART_2_BASE      0xFF201008
#define IrDA_BASE             0xFF201020
#define TIMER_BASE            0xFF202000
#define AV_CONFIG_BASE        0xFF203000
#define PIXEL_BUF_CTRL_BASE   0xFF203020
#define CHAR_BUF_CTRL_BASE    0xFF203030
#define AUDIO_BASE            0xFF203040
#define VIDEO_IN_BASE         0xFF203060
#define ADC_BASE              0xFF204000

/* Cyclone V HPS devices */
#define HPS_GPIO1_BASE        0xFF709000
#define HPS_TIMER0_BASE       0xFFC08000
#define HPS_TIMER1_BASE       0xFFC09000
#define HPS_TIMER2_BASE       0xFFD00000
#define HPS_TIMER3_BASE       0xFFD01000
#define FPGA_BRIDGE           0xFFD0501C

/* ARM A9 MPCORE devices */
#define   PERIPH_BASE         0xFFFEC000    // base address of peripheral devices
#define   MPCORE_PRIV_TIMER   0xFFFEC600    // PERIPH_BASE + 0x0600

/* Interrupt controller (GIC) CPU interface(s) */
#define MPCORE_GIC_CPUIF      0xFFFEC100    // PERIPH_BASE + 0x100
#define ICCICR                0x00          // offset to CPU interface control reg
#define ICCPMR                0x04          // offset to interrupt priority mask reg
#define ICCIAR                0x0C          // offset to interrupt acknowledge reg
#define ICCEOIR               0x10          // offset to end of interrupt reg
/* Interrupt controller (GIC) distributor interface(s) */
#define MPCORE_GIC_DIST       0xFFFED000    // PERIPH_BASE + 0x1000
#define ICDDCR                0x00          // offset to distributor control reg
#define ICDISER               0x100         // offset to interrupt set-enable regs
#define ICDICER               0x180         // offset to interrupt clear-enable regs
#define ICDIPTR               0x800         // offset to interrupt processor targets regs
#define ICDICFR               0xC00         // offset to interrupt configuration regs

int radii = 5;
int head_x, head_y;
int food_x = 30, food_y = 110;
int initial_x = 160, initial_y = 110;
int score = 0;
int level = 1;
int dir_x = -1, dir_y = 0;
const int snake_length = 3;
volatile int pixel_buffer_start;
int flag = 0;
int gameover = 0;
int alpha = 0;

typedef struct Block
{
    int x;
    int y;
} block;

block block_list[10] = {{30, 110},{260, 30},{100, 100},{30, 140},{190, 170},{70, 30},{250, 160},{160, 50},
    {110, 100},{200, 160}};

void swap(int *p1, int *p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void write_pixel(int x, int y, int clr)
{
    volatile short *_vga_addr = (volatile short *)(0x08000000 + (y << 10) + (x << 1));
    *_vga_addr = clr;
}

void clear_screen()
{
    int x, y;
    for (x = 0; x < 320; x++){
        for (y = 0; y < 240; y++){
            write_pixel(x, y, 0);
        }
    }
}

void write_char(int x, int y, char c)
{
    volatile char *_character_buffer = (char *)(0x09000000 + (y << 7) + x);
    *_character_buffer = c;
}

void draw_footer(){
    char* hw = "Level: ";
    int x = 5;
    while (*hw) {
        write_char(x, 52, *hw);
        x++;
        hw++;
    }
    char str[5];

    sprintf(str, "%d", level);
    x = 15;
    int a=0;
    while (a<5) {
        write_char(x, 52, str[a]);
        x++;
        a++;
    }

    char* hw1 = "Score: ";
    x = 5;
    while (*hw1) {
        write_char(x, 55, *hw1);
        x++;
        hw1++;
    }
    char str1[5];
    sprintf(str1, "%d", score);
    x = 15;
    a=0;
    while (a<5) {
        write_char(x, 55, str1[a]);
        x++;
        a++;
    }

    char* hw2 = "Move: ";
    char* hw3 = "Up -> 0    Down -> 3";
    char* hw4 = "Left -> 1  Right -> 2";

    x = 30;
    while(*hw2){
        write_char(x, 52, *hw2);
        x++;
        hw2++;
    }
    x = 30;
    while(*hw3){
        write_char(x, 54, *hw3);
        x++;
        hw3++;
    }
    x = 30;
    while(*hw4){
        write_char(x, 56, *hw4);
        x++;
        hw4++;
    }
    
}

void draw_board_1()
{
    int i, j;
    for (i = 190; i < 200; i++){
        for (j = 0; j < 320; j++){
            write_pixel(j, i, 0xf800);
        }
    }
	
	for (i = 0; i <= 10; i++){
        for (j = 0; j < 320; j++){
            write_pixel(j, i, 0xf800);
        }
    }
	
	for (i = 0; i < 200; i++){
        for (j = 0; j <= 10; j++){
            write_pixel(j, i, 0xf800);
        }
    }
	
	for (i = 0; i < 200; i++){
        for (j = 310; j < 320; j++){
            write_pixel(j, i, 0xf800);
        }
    }	

    for(i = 200;i < 240; i++){
        for(j = 0; j < 320; j++){
            write_pixel(j, i, 0x0);
        }
    }
}

void draw_board_2(){

    int i, j;
    draw_board_1();
    for (i = 70; i <= 80; i++){
        for (j = 120; j < 200; j++){
            write_pixel(j, i, 0xf800);
        }
    }

    for (i = 130; i <= 140; i++){
        for (j = 120; j < 200; j++){
            write_pixel(j, i, 0xf800);
        }
    }
}

void draw_board_3(){
    int i, j;
    draw_board_1();

    for (i = 70; i < 80; i++){
        for (j = 120; j < 200; j++){
            if(j<=180 && j>=140) continue;

            write_pixel(j, i, 0xf800);
        }
    }

    for (i = 130; i < 140; i++){
        for (j = 120; j < 200; j++){
            if(j<=180 && j>=140) continue;
            write_pixel(j, i, 0xf800);
        }
    }

    for (i = 70; i < 140; i++){
        for (j = 110; j < 120; j++){
            if(i>=90 && i<=120) continue;
            write_pixel(j, i, 0xf800);
        }
    }

    for (i = 70; i < 140; i++){
        for (j = 200; j < 210; j++){
            if(i>=90 && i<=120) continue;
            write_pixel(j, i, 0xf800);
        }
    }

}

void update_level(){
    char str[5];
    sprintf(str, "%d", level);
    int x = 15;
    int a=0;
    while (a<5) {
        write_char(x, 52, str[a]);
        x++;
        a++;
    }
}

void update_score(){
    
    char str[5];
    sprintf(str, "%d", score);
    int x = 15;
    int a=0;
    while (a<5) {
        write_char(x, 55, str[a]);
        x++;
        a++;
    }
}

int check_collision_1(int a, int b){
    if(a-radii <= 10){
        return 1;
    }
    if(a+radii >= 310){
        return 1;
    }

    if(b-radii <= 10){
        return 1;
    }
    if(b+radii >= 190){
        return 1;
    }

    return 0;
}

int check_collision_3(int a, int b){
    if(check_collision_1(a, b)){
        return 1;
    }
    if((a+radii >= 120 && a-radii <= 140) && (b - radii <= 80 && b + radii >= 70)){
        return 1;
    }
    if((a+radii >= 180 && a-radii <= 200) && (b - radii <= 80 && b + radii >= 70)){
        return 1;
    }
    if((a+radii >= 120 && a-radii <= 140) && (b - radii <= 140 && b + radii >= 130)){
        return 1;
    }
    if((a+radii >= 180 && a-radii <= 200) && (b - radii <= 140 && b + radii >= 130)){
        return 1;
    }
    if((a+radii >= 110 && a-radii <= 120) && (b + radii >= 70 && b + radii <= 90)){
        return 1;
    }
    if((a+radii >= 110 && a-radii <= 120) && (b + radii >= 120 && b - radii <= 140)){
        return 1;
    }
    if((a+radii >= 200 && a-radii <= 210) && (b + radii >= 120 && b - radii <= 140)){
        return 1;
    }
    if((a+radii >= 200 && a-radii <= 210) && (b + radii >= 70 && b - radii <= 90)){
        return 1;
    }
    
    return 0;
}

int check_collision_2(int a, int b){
    if(check_collision_1(a, b)){
        return 1;
    }
    if((a + radii >= 120 && a - radii <= 200) && (b - radii <= 80 && b + radii >= 70)){
        return 1;
    }
    if((a + radii >= 120 && a - radii <= 200) && (b - radii <= 140 && b + radii >= 130)){
        return 1;
    }

    return 0;
}

void draw_snake(int node_x[], int node_y[]){
    head_x = 160, head_y = 110;
	int temp = head_x;
    int color;
    for(int k=0;k<snake_length;k++){
        if(k%2==0) color = 0x00afb9;
		else color = 0x0081a7;
		if(k==0) color = 0xffffff;
        for (int i = -radii; i <= radii; i++) {
            for (int j = -radii; j <= radii; j++) {
            	write_pixel((int)(head_x + i), (int)(head_y + j), color);
            }
        }
        node_x[k] = head_x;
        node_y[k] = head_y;
        head_x += 2*radii;
    }
	head_x = temp;
}

void draw_food(){
	int len = radii;
    for(int i=-len;i<len;i++){
        for(int j=-len;j<len;j++){
            if(i*i + j*j <= len*len)
           	write_pixel((int)(food_x + i), (int)(food_y + j), 0xFFAE42);
        }
    }
}

void clear_food(){
    int len = radii;
    for(int i=-len;i<len;i++){
        for(int j=-len;j<len;j++){
           	write_pixel((int)(food_x + i), (int)(food_y + j), 0);
        }
    }
}

void erase_snake(int node_x[], int node_y[]){
    for(int i=0;i<snake_length;i++){
        for(int x=-radii;x<=radii;x++){
            for(int y=-radii;y<=radii;y++){
                write_pixel(node_x[i] + x, node_y[i] + y, 0);
            }
        }
    }
}

int isEaten(int a, int b){
    if((a-food_x)*(a-food_x) + (b-food_y)*(b-food_y) <= 4*(radii)*(radii)){
        return 1;
    }

    return 0;
}

void change_direction(int val){
    int curr_x = dir_x, curr_y = dir_y;
    if(val == 1){
        if(curr_x == 0 && curr_y == 1) return;
        dir_x = 0;
        dir_y = -1;
    } else if(val == 2){
        if(curr_x == 1 && curr_y == 0) return;
        dir_x = -1;
        dir_y = 0;
    } else if(val == 4){
        if(curr_x == -1 && curr_y == 0) return;
        dir_x = 1;
        dir_y = 0;
    } else if(val == 8){
        if(curr_x == 0 && curr_y == -1) return;
        dir_x = 0;
        dir_y = 1;
    }
}

void move(int k, int node_x[], int node_y[]){
    int clr = 0xffffff;
    int temp_x, temp_y;
    if(k==0){
        for(int i=-radii;i<=radii; i++){
            for(int j=-radii;j<=radii;j++){
                write_pixel(node_x[k] + i, node_y[k] + j, 0);
            }
        }
        temp_x = node_x[k], temp_y = node_y[k];
        if(dir_x == -1){
            node_x[k] -= 2*radii;
        } else if(dir_x == 1){
            node_x[k] += 2*radii;
        }

        if(dir_x == 0){
            if(dir_y == -1){
                node_y[k] -= 2*radii;
            } else if(dir_y == 1){
                node_y[k] += 2*radii;
            }
        }

        if(isEaten(node_x[0], node_y[0])){
            clear_food();
            score += 10;
            update_score();
            if(score >= 50 && level == 1){
                draw_board_2();
                level++;
                erase_snake(node_x, node_y);
                draw_snake(node_x, node_y);
                change_direction(2);
                update_level();
            } else if(score >= 100 && level == 2){
                draw_board_3();
                level++;
                erase_snake(node_x, node_y);
                draw_snake(node_x, node_y);
                change_direction(2);
                update_level();
            }
            food_x = block_list[alpha].x;
            food_y = block_list[alpha].y;
            alpha++;
            alpha = alpha%10;
            draw_food();
        }
        for(int y=-radii;y<=radii;y++){
            for(int x=-radii;x<=radii;x++){
                write_pixel((int)(node_x[k] + x), (int)(node_y[k] + y), clr);
            }
        }
    } else {
        if(k==1){
            clr = 0x0081a7;    
        } else if(k==2){
            clr = 0x00afb9;
        }
        for(int i=-radii;i<=radii; i++){
            for(int j=-radii;j<=radii;j++){
                write_pixel(node_x[k] + i, node_y[k] + j, 0);
            }
        }
        swap(&node_x[k], &temp_x);
        swap(&node_y[k], &temp_y);
        for(int i=-radii;i<=radii; i++){
            for(int j=-radii;j<=radii;j++){
                write_pixel(node_x[k] + i, node_y[k] + j, clr);
            }
        }
    } 
}


int main()
{
    start_again:;
    int node_x[snake_length], node_y[snake_length];
    score = 0;
    level = 1; 
    clear_screen();
    draw_board_1();
    draw_footer();
    draw_snake(node_x, node_y);
    draw_food();
    update_level();
    update_score();
    change_direction(2);
    gameover = 0;
    time_t t;
    srand((unsigned)time(&t));
    while(!gameover){
        int val;
        val = *PUSHBUTTONS;
        change_direction(val);
        for(int i=0;i<3;i++){
            for(int i=0;i<500000;i++){}
            move(i, node_x, node_y);
        }
        
        if(level == 1){
            if(check_collision_1(node_x[0], node_y[0])){
                gameover = 1;
            }
        } else if(level == 2){
            if(check_collision_2(node_x[0], node_y[0])){
                gameover = 1;
            }
        } else if(level == 3){
            if(check_collision_3(node_x[0], node_y[0])){
                gameover = 1;
            }
        }
        for(int i=0;i<500000;i++){}
    }

    int ct = 0;

    while (ct < 50000000)
    {
        ct++;
    }
    alpha++;
    alpha = alpha%10;

    goto start_again;

    
    return 0;
}