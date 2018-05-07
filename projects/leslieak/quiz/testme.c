#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    char character = "[](){}axrest "[random () % 13];
    return character;
}

char *inputString()
{
	int i;
    // TODO: rewrite this function
	char *string = (char *) malloc(sizeof(char) * 10);
    for(i=0; i < 10; i++){
    	string[i] = "[](){}0axrset "[random () % 14];
    	if(string[i] == '0') {
    		string[i] = '\0';
    	}
    }
    return string;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  time_t  end;
  int secs = 300;

end= time(NULL)+secs;

while(time(NULL) < end){
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
