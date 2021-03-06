/** Name -> Abhay Shanker Pathak
Date -> 2020-03-09
Description -> Find the sum of the just previous three terms before nth term through recursion
Email -> abhaysp9955@gmail.com
Github -> https://github.com/CoolAbhayS
Last Edit -> 2020-03-09 */

#include<stdio.h>

int find_nth_term(int ,int ,int ,int );

int main(int argc, char *argv[]){
	int n, a, b, c;
	printf("\nEnter the nth term: ");
	scanf("%d", &n);
	printf("\nEnter the first three starting terms for series: ");
	scanf("%d%d%d", &a, &b, &c);

	// function for finding sum
	int ans = find_nth_term(n - 3, a, b, c);
	printf("\nSum of the last third elements for %dth element is: %d", n, ans);
	return 0;
}

int find_nth_term(int n, int a, int b, int c) {
		/* c += a + b; */
		/* b = c - (a + b); */
		/* a  = c - b - a; */
		/* /1* a = b; *1/ */
		/* /1* b = c; *1/ */
	/* if (n != 0) */
		/* find_nth_term(n - 1, a, b, c); */
	/* else */
		/* return c; */
	if (n != 0)
		return find_nth_term(n - 1, b, c, a + b + c);
	else
		return c;
}
