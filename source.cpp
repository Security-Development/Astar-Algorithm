#include <stdio.h>
#include <math.h>
#include <windows.h>
#define WEIGHT 14
#define MAP_SIZE 20
#define DIRECT 8

int map[MAP_SIZE][MAP_SIZE] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
	{0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, },
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, },
};

/*
	  	 3   
	     │	
	1 ---O--- 0
	     │
	 	 2 
*/
 // 동 -> 서 -> 남 -> 북 순서 
int dx[8] = {1, -1, 0, 0, 1, -1, 1, -1};
int dy[8] = {0, 0, -1, 1, 1, 1, -1, -1};
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

void view_map() {
	system("cls");
	for(int i = 0; i < MAP_SIZE; i++) {
		for(int j = 0; j < MAP_SIZE; j++) {
			if(map[i][j] == 0) {
				if( start.x == i && start.y == j ) {
					printf("☆");
				} else if( end.x == i && end.y == j ) {
					printf("★");
				} else  {
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
	while( target->visit != 1 ) {
		if( (target->x == end.x && target->y == end.y)) 
			break;
		
		if( target->visit == 0 )
			target->visit = 1;
			
		 // 방문 처리 
		//target.list = 1;

		for(int i = 0; i < DIRECT; i++) {
			Node next;
				
			next.x = target->x + dx[i];
			next.y = target->y + dy[i];
			next.g = target->g + 14; //  이동거리
			next.h = getHuristic(&next, &end); 
			next.f = next.g + next.h;
			
			if( 
				map[next.x][next.y] == 1 || 
				(map[next.x + 1][next.y] == 1 && map[next.x][next.y - 1] == 1 && map[next.x - 1][next.y] == 1) ||
				(map[next.x][next.y - 1] == 1 && map[next.x -1][next.y] == 1 && map[next.x][next.y + 1] == 1) ||
				(map[next.x][next.y + 1] == 1 && map[next.x -1][next.y] == 1 && map[next.x + 1][next.y] == 1) ||
				(map[next.x + 1][next.y] == 1 && map[next.x][next.y - 1] == 1 && map[next.x][next.y + 1] == 1) ||
				next.x < 0 || next.y < 0 || 
				next.x > MAP_SIZE - 1  || next.y > MAP_SIZE - 1 
				
				)
				continue;
				
			//map[next.x][next.y] = 2;
				
			
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
				if( OpenList[i].visit == 0 && OpenList[j].visit == 0 ) {
					if( OpenList[i].f > OpenList[j].f) {
						Node temp = OpenList[i];
						OpenList[i] = OpenList[j];
						OpenList[j] = temp;
						
						//OpenList[i] ^= *OpenList[j] ^= OpenList[i] ^= OpenList[j]; // xor swap algorithnm
					}
				}
			}
		}
		

		for(int i = 0; i < count; i++) {
			if( OpenList[i].visit == 0 ) {
				backtracking(&OpenList[i]);
				break;
			} 
		}				
	}
}

int is_OpenList(int x, int y) {
	for(int i = 0; i < count; i++) {
		if( OpenList[i].x == x && OpenList[i].y == y ) 
			return i;
	}
	
	return 0;
}

void path(Node *target) {
	
	if( map[target->x][target->y] != 2 )
		map[target->x][target->y] = 2;
	
	if( target->x == start.x && target->y == start.y )
		return;
		
	Node *a = (Node *)malloc(sizeof(struct Node) * 8);
	int a_count = 0;
	
	for(int i = 0; i < DIRECT; i++) {
		int temp = is_OpenList(target->x + dx[i] , target->y + dy[i]);
		
		if( temp > 0) 
			a[a_count++] = OpenList[temp];

	} 
	
	if( a[0].g == 0) {
		printf("길을 찾을 수 없습니다.\n");
		return;	
	}
	
	Node min = a[0];
	for(int i = 1; i < a_count; i++) {
		if( min.g > a[i].g && a[i].g != 0 )
			min = a[i];
	}
	
	for(int i = 0; i < a_count; i++) {
		if ( a[i].x == start.x && a[i].y == start.y ) {
			min = a[i];
			break;
		}
	}
	
	free(a);
	view_map();
	path(&min);	

}
	
int main() {
	start.x = 2;
	start.y = 3;
	start.f = getHuristic(&start, &end);
	end.x = 15;
	end.y = 15;
	end.f = getHuristic(&end, &end);
	
	backtracking(&start);
	path(&end);

}
