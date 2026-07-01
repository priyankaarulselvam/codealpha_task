#include<stdio.h>
int main()
{
	int a,b,ch;
	printf("enter a values:");
	scanf("%d %d",&a,&b);
	printf("enter a choice:");
	scanf("%d",&ch);
	switch(ch)
	{
	case 1:
		printf("Result=%d",a+b);
		break;
	case 2:
		printf("Result=%d",a-b);
		break;
	case 3:
		printf("Result=%d",a*b);
		break;
	case 4:
		if (b!=0)
		{
			printf("Result=%.2f",(float)a/b);
		}
		else
		{
			printf("Not able to perform a operation");
		}
		break;
		default:
		printf("Invalid choice");
	}
	return 0;
}