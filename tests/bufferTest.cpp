#include "../libs/buffer.h"
#include <stdio.h>

int main(int argc, char const *args[]){
	buffer one;
	one="one";
	one+=(char)0;
	printf("%d\n%s\n",one.length,one.buf);

	buffer two;
	two="two";
	two+=(char)0;
	printf("%d\n%s\n",two.length,two.buf);

	buffer comb;
	comb=one;
	comb+=two;
	printf("%d\n%s\n",comb.length,comb.buf);
	return 0;
}