#include <iostream>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <MMsystem.h>
#include <thread>
using namespace std;

class Stack{
protected:
	int stack[500][2];
	int top, size;
public:
	Stack() {
		top = -1;
		size = 500;
	}
	~Stack() {
		while(isEmpty() != true)
			pop();
	}
	bool isEmpty() {
		return top == -1;
	}
	bool isFull() {
		return top == size-1;
	}
	void push(int i, int j) {
		if(isFull()) {
			return;
		}
		else if(isEmpty()) {
			top = 0;
			stack[top][0] = i;
			stack[top][1] = j;
		}
		else {
			top++;
			stack[top][0] = i;
			stack[top][1] = j;
		}
	}
	void pop() {
		if(isEmpty())
			return;
		top--;
	}
	int* peek() {
		if(isEmpty())
			return nullptr;
		return stack[top];
	}
};

class Queue {
private:
	int queue[250][2], rear, front;
public:
	Queue() {
		rear = -1;
		front = -1;
	}
	~Queue() {
		while(isEmpty() != true)
			dequeue();
	}
	bool isEmpty() {
		if(rear == -1 && front == -1)
			return true;
		else
			return false;
	}
	bool isFull() {
		if(rear == 250)
			return true;
		else
			return false;
	}
	void enqueue(int i, int j) {
		if(isFull()) {
			return;
		}
		else if(isEmpty()) {
			rear = 0;
			front = 0;
			queue[rear][0] = i;
			queue[rear][1] = j;
		}
		else {	
			rear ++;
			queue[rear][0] = i;
			queue[rear][1] = j;
		}
	}
	void dequeue() {
		if(isEmpty()) {
			return;
		}
		else if(front == rear){
			front = -1;
			rear = -1;
		} else {
			front ++;
		}
	}
	int* getfront() {
		if(isEmpty()) {
			return nullptr;
		} else {
			return queue[front];
		}
	}
};

class Maze {
protected:
	Stack s;
	char map[25][25];
	int i, j, x, y;
public:
	void playmusic() {
			PlaySound(TEXT("Undertale OST - 059 Spider Dance.wav"), NULL, SND_ASYNC);
	}
	void generate_map() {	
		for(i = 0; i < 25; i++)
			for(j = 0; j < 25; j++)
				map[i][j] = '#';
	}
	void print_map() {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		for(i = 0; i < 25; i++) {
			for(j = 0; j < 25; j++) {
				if(map[i][j] == '#')
      				SetConsoleTextAttribute(h, 4);
      			else
      				SetConsoleTextAttribute(h, 10);
				cout << map[i][j] << " ";
			}
			cout << endl;
		}
	}
	void generate_path() {
		srand(time(0));
		x = 1;
		y = 1;
		while(x != 23 || y != 23) {
			if((rand()%13 >= 0 and rand()%13 < 4) and y != 23)
				map[x][++y] = ' ';
		 	if((rand()%13 >= 4 and rand()%13 < 8) and x != 23) 
				map[++x][y] = ' ';
			if(rand()%13 == 8 and x != 1)
				map[--x][y] = ' ';
			if(rand()%13 == 9 and y != 1)
				map[x][--y] = ' ';
			if(rand()%13 == 10 and x != 23 and y != 1)
				map[++x][--y] = ' ';
			if(rand()%13 == 11 and x != 1 and y != 23)
				map[--x][++y] = ' ';
			if(rand()%13 == 12 and x != 23 and y != 23)
				map[++x][++y] = ' ';
			if(rand()%13 == 13 and x != 1 and y != 1 )
				map[--x][--y] = ' ';
			}
		}
	void generate_branch() {
		for(int bar = 0; bar < 100; bar++) {
			x = rand() %22 + 1;
			y = rand() %22 + 1;
			if(map[x][y] != ' ') {
				while(map[x][y] != ' ') {
					x = rand() %22 + 1;
					y = rand() %22 + 1;				
				}
			}
			while(x != 23 || y != 23) {
				if(rand() % 7 == 0 and x != 1)
					x--;
				else if(rand() % 7 == 1 and y != 1)
					y--;
				else if(rand() % 7 == 2 and x != 23)
					x++;
				else if(rand() % 7 == 3 and y != 23)
					y++;
				else if(rand() % 7 == 4 and x != 23 and y != 23) {
					x++;
					y++;
				}
				else if(rand() % 7 == 5 and x != 1 and y != 23) {
					x--;
					y++;
				}
				else if(rand() % 7 == 6 and x != 23 and y != 1) {
					x++;
					y--;
				}
				else if(rand() % 7 == 7 and x != 1 and y != 1) {
					x--;
					y--;
				}
				if(map[x][y] == '#' and ((map[x - 1][y] != ' ' and map[x][y - 1] != ' ' and map[x - 1][y - 1] != ' ' and map[x + 1][y - 1] != ' ')
				|| (map[x][y + 1] != ' ' and map[x + 1][y] != ' ' and map[x + 1][y + 1] != ' ' and map[x - 1][y + 1] != ' ')))
					map[x][y] = ' ';
			}
		}
		map[23][23] = 'E';
	}
};

class Traverse_with_queue : Maze {
private:
	Queue q;
	int i, j;
	int* topLocation = nullptr;
	bool checked[25][25];
public:
	void start() {
		generate_map();
		generate_path();
		generate_branch();
	}
	void check_path(int i, int j) {
		if(map[i][j+1] == ' '){
			if(checked[i][j+1] == false)
				q.enqueue(i,j+1);
			checked[i][j+1] = true;
		}
		if(map[i][j-1] == ' ') {
			if(checked[i][j-1] == false)
				q.enqueue(i,j-1);
			checked[i][j-1] = true;
		}
		if(map[i-1][j] == ' ') {
			if(checked[i-1][j] == false)
				q.enqueue(i-1,j);
			checked[i-1][j] = true;
		}
		if(map[i+1][j] == ' ') {
			if(checked[i+1][j] == false)
				q.enqueue(i+1,j);
			checked[i+1][j] = true;
		}	
		if(map[i+1][j+1] == ' ') {
			if(checked[i+1][j+1] == false)
				q.enqueue(i+1,j+1);
			checked[i+1][j+1] = true;
		}
		if(map[i-1][j-1] == ' ') {
			if(checked[i-1][j-1] == false)
				q.enqueue(i-1,j-1);
			checked[i-1][j-1] = true;
		}
		if(map[i+1][j-1] == ' ') {
			if(checked[i+1][j-1] == false)
				q.enqueue(i+1,j-1);
			checked[i+1][j-1] = true;
		}
		if(map[i-1][j+1] == ' ') {
			if(checked[i-1][j+1] == false)
				q.enqueue(i-1,j+1);
			checked[i-1][j+1] = true;
		}
	}
	void uncheck() {
		for(i=0; i<25; i++)
			for(j=0; j<25; j++)
				checked[i][j] = false;
	}
	void traverse() {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		map[1][1] = 'X';
		i = 1;
		j = 1;
		check_path(i,j);
		print_map();
		while(1) {
			if(map[i+1][j] == 'E' || map[i][j+1] == 'E' || map[i+1][j+1] == 'E' || map[i-1][j-1] == 'E'
			 || map[i+1][j-1] == 'E' || map[i-1][j+1] == 'E' || map[i-1][j] == 'E' || map[i][j-1] == 'E' || map[i][j] == 'E') {
			 	SetConsoleTextAttribute(h, 10);
			 	q.~Queue();
			 	uncheck();
				cout << endl << "moosh ba movafaghiat az maze kharej shod!" << endl;
				break;
			}
			if(map[i][j+1] == ' ') {
				map[i][++j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i+1][j] == ' ') {
				map[++i][j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i][j-1] == ' ') {
				map[i][--j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i-1][j] == ' ') {
				map[--i][j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i-1][j+1] == ' ') {
				map[--i][++j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i+1][j-1] == ' ') {
				map[++i][--j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i-1][j-1] == ' ') {
				map[--i][--j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i+1][j+1] == ' ') {
				map[++i][++j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i+1][j] == 'E' || map[i][j+1] == 'E' || map[i+1][j+1] == 'E' || map[i-1][j-1] == 'E'
			 || map[i+1][j-1] == 'E' || map[i-1][j+1] == 'E' || map[i-1][j] == 'E' || map[i][j-1] == 'E' || map[i][j] == 'E') {
			 	q.~Queue();
			 	uncheck();
				SetConsoleTextAttribute(h, 10);
				cout << endl << "moosh ba movafaghiat az maze kharej shod!" << endl;
				break;
			}
			q.dequeue();
			topLocation = q.getfront();
			if(topLocation != nullptr) {
				i = topLocation[0];
				j = topLocation[1];
			}
		}        
	}
};

class Traverse_with_stack : Maze {
private:
	Stack s;
	int i, j;
	int* topLocation = nullptr;
	bool checked[25][25];
public:
	void start() {
		generate_map();
		generate_path();
		generate_branch();
	}
	void check_path(int i, int j) {
		if(map[i+1][j] == ' '){
			if(checked[i+1][j] == false) {
				s.push(i,j);
				s.push(i+1,j);
			}
			checked[i+1][j] = true;
		}
		if(map[i][j+1] == ' ') {
			if(checked[i][j+1] == false) {
				s.push(i,j);
				s.push(i,j+1);
			}
			checked[i][j+1] = true;
		}
		if(map[i][j-1] == ' ') {
			if(checked[i][j-1] == false) {
				s.push(i,j);
				s.push(i,j-1);
			}
			checked[i][j-1] = true;
		}
		if(map[i-1][j] == ' ') {
			if(checked[i-1][j] == false) {
				s.push(i,j);
				s.push(i-1,j);
			}
			checked[i-1][j] = true;
		}	
		if(map[i+1][j+1] == ' ') {
			if(checked[i+1][j+1] == false) {
				s.push(i,j);
				s.push(i+1,j+1);
			}
			checked[i+1][j+1] = true;
		}
		if(map[i-1][j-1] == ' ') {
			if(checked[i-1][j-1] == false) {
				s.push(i,j);
				s.push(i-1,j-1);
			}
			checked[i-1][j-1] = true;
		}
		if(map[i+1][j-1] == ' ') {
			if(checked[i+1][j-1] == false) {
				s.push(i,j);
				s.push(i+1,j-1);
			}	
			checked[i+1][j-1] = true;
		}
		if(map[i-1][j+1] == ' ') {
			if(checked[i-1][j+1] == false) {
				s.push(i,j);
				s.push(i-1,j+1);
			}	
			checked[i-1][j+1] = true;
		}
	}
	void uncheck() {
		for(i=0; i<25; i++)
			for(j=0; j<25; j++)
				checked[i][j] = false;
	}
	void traverse() {
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		map[1][1] = 'X';
		i = 1;
		j = 1;
		check_path(i,j);
		print_map();
		while(1) {
			if(map[i+1][j] == 'E' || map[i][j+1] == 'E' || map[i+1][j+1] == 'E' || map[i-1][j-1] == 'E'
			 || map[i+1][j-1] == 'E' || map[i-1][j+1] == 'E' || map[i-1][j] == 'E' || map[i][j-1] == 'E' || map[i][j] == 'E') {
			 	SetConsoleTextAttribute(h, 10);
			 	s.~Stack();
			 	uncheck();
				cout << endl << "moosh ba movafaghiat az maze kharej shod!" << endl;
				break;
			}
			if(map[i][j+1] == ' ') {
				map[i][++j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i+1][j] == ' ') {
				map[++i][j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i][j-1] == ' ') {
				map[i][--j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i-1][j] == ' ') {
				map[--i][j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i-1][j+1] == ' ') {
				map[--i][++j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i+1][j-1] == ' ') {
				map[++i][--j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i-1][j-1] == ' ') {
				map[--i][--j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i+1][j+1] == ' ') {
				map[++i][++j] = 'X';
				check_path(i,j);
				system("cls");
				print_map();
				_sleep(20);
				continue;
			}
			if(map[i+1][j] == 'E' || map[i][j+1] == 'E' || map[i+1][j+1] == 'E' || map[i-1][j-1] == 'E'
			 || map[i+1][j-1] == 'E' || map[i-1][j+1] == 'E' || map[i-1][j] == 'E' || map[i][j-1] == 'E' || map[i][j] == 'E') {
			 	s.~Stack();
			 	uncheck();
				SetConsoleTextAttribute(h, 10);
				cout << endl << "moosh ba movafaghiat az maze kharej shod!" << endl;
				break;
			}
			s.pop();
			topLocation = s.peek();
			if(topLocation != nullptr) {
				i = topLocation[0];
				j = topLocation[1];
			}
		}        
	}
};

int main() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	Maze m;
	Stack s;
	thread musicThread([&m] { 
	 	m.playmusic();
  	});
	Traverse_with_stack ts;
	Traverse_with_queue tq;
	char n = '0';
	while(true) {
		SetConsoleTextAttribute(h, 15);
		cout <<"1.Traverse_with_stack" << endl << "2.Traverse_with_queue" << endl  << "3.Exit\n" << endl;
		n = getch();
		switch(n) {
			case '1':
				ts.start();
				ts.traverse();
				cout << endl;
				break;
			case '2':
				tq.start();
				tq.traverse();
				cout << endl;
				break;	
			case '3':
				musicThread.join();
				system("cls");
				cout << "Ba Tashakor az tavajoh shoma!";
				return 0;
			default:
				system("cls");
				cout << "please enter numbers 1,2 or 3" << endl;
		}
	}
	return 0;
}