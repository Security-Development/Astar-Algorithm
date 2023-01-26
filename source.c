#include <stdio.h>
#include <math.h>
#include <windows.h>
#define WEIGHT 10
#define MAP_SIZE 20

int map[MAP_SIZE][MAP_SIZE] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
};

/*
	  	 3   
	     │	
	1 ---O--- 0
	     │
	 	 2 
*/
 // 동 -> 서 -> 남 -> 북 순서 
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int count = 0;

typedef struct Node { 
	int f = 0, 
		g = 0, 
		h = 0, 
		x = 0, 
		y = 0,
		visit = 0,
		list = 0; 
		
		Node *prant = NULL;
} Node;

Node OpenList[MAP_SIZE * MAP_SIZE];
Node start;
Node end;

int getHuristic(Node *target, Node *end) {
	int x = abs(target->x - end->x);	
	int y = abs(target->y - end->y);
	int value = abs(x - y);
	return (WEIGHT * (sqrt(pow(x, 2) + sqrt(pow(y, 2)))));
}


int getG(Node target) {
	return target.prant->g + 1;
}


void view_map() {
	system("cls");
	for(int i = 0; i < MAP_SIZE; i++) {
		for(int j = 0; j < MAP_SIZE; j++) {
			if(map[i][j] == 0) {
				if( start.x == i && start.y == j ) {
					printf("☆");
				} else if( end.x == i && end.y == j ) {
					printf("★");
				}  {
					printf("□");
				}
				
			} else if( map[i][j] == 2) {
				printf("* ");
			} else {
				printf("■");
			} 
		}
		printf("\n");
	}
}

void backtracking(Node *target) { 
	while( target->visit != 1) {
		if( (target->x == end.x && target->y == end.y)) 
			break;
		
		if( target->visit == 0 )
			target->visit = 1;
			
		 // 방문 처리 
		//target.list = 1;

		for(int i = 0; i < 4; i++) {
			Node next;
			next.x = target->x + dx[i];
			next.y = target->y + dy[i];
			next.g = target->g + 1; //  이동거리
			next.h = getHuristic(&next, &end); 
			next.f = next.g + next.h;
			
			if( map[next.x][next.y] == 1 || next.x < 0 || next.y < 0 || next.x > MAP_SIZE - 1  || next.y > MAP_SIZE - 1)
				break;
				
			map[next.x][next.y] = 2;
				
			if( target->prant != NULL ) 
				next.prant = target;
			
			int check = 0;
			for(int i = 0; i < count; i++){
				if( (next.x == OpenList[i].x && next.y == OpenList[i].y) ) {
					check = 1;
				}
			}
			
			if(check == 0 )
				OpenList[count++] = next;
		}
	
		for(int i = 0; i < count - 1; i++) {			
			for(int j = i + 1; j < count; j++) {
				if(OpenList[i].visit == 0 && OpenList[j].visit == 0) {
					if( OpenList[i].f > OpenList[j].f) {
						Node temp = OpenList[i];
						OpenList[i] = OpenList[j];
						OpenList[j] = temp;
						
						//OpenList[i] ^= *OpenList[j] ^= OpenList[i] ^= OpenList[j]; // xor swap algorithnm
					}
				}
			}
		}
		
		view_map();
		printf("\n");
		for(int i = 0; i < count; i++) {
			if( OpenList[i].visit == 0 ) {
				backtracking(&OpenList[i]);
				break;
			} 
		}
		
		
		
	}
}
	
int main() {
	start.x = 3;
	start.y = 3;
	end.x = 15;
	end.y = 15;

	backtracking(&start);
	
	//printf("huristic : %d", getHuristic(start, end));
}
