#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct
{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char **HuffmanCode;

void Select(HuffmanTree *Ht,int k,int *s1,int *s2)
{ 
	int j,min; 
	for(j=1;j<=k;j++)
	{
		if((*Ht)[j].parent==0) 
	    {
			min=j;            
			break;  
		}
	}   
	for(j=1;j<=k;j++) 
	{  
		if((*Ht)[j].parent==0) 
		{   
			if((*Ht)[j].weight<(*Ht)[min].weight) 
		    min=j;  
		}
	}   
	*s1=min; 
	for(j=1;j<=k;j++) 
	{  
		if((*Ht)[j].parent==0 && j!=(*s1)) 
		{   
			min=j;            
			break;  
		} 
	}   
	for(j=1;j<=k;j++)
	{  
		if((*Ht)[j].parent==0 && j!=(*s1))
		{  
			if((*Ht)[j].weight<(*Ht)[min].weight) 
			min=j;  
		} 
	}  
	*s2=min;
}
void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
{
	if(n<=1)
	return;
	int m,i;
	HuffmanTree p;
	m=2*n-1;
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
	int s1,s2;
	for(p=HT,i=0;i<=n;++i,++w,++p)    
	{
		p->weight=*w;
		p->parent=0;
		p->lchild=0;
    	p->rchild=0;
	}
	for(;i<=m;++i,++p)
	{
		p->weight=0;
		p->parent=0;
		p->lchild=0;
    	p->rchild=0;
	}
	printf("\n");
	for(i=n+1;i<=m;++i)
	{
		int s1,s2;
		Select(&HT,i-1,&s1,&s2);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight; 
		printf("%d (%d, %d)\n",(HT)[i].weight,(HT)[s1].weight,(HT)[s2].weight);   
	}
	char *cd;
	int start,f;
	unsigned int c;
	HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
	cd=(char *)malloc(n*sizeof(char));
	cd[n-1]='\0';
	for(i=1;i<=n;++i)
	{
		start=n-1;
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
		if(HT[f].lchild==c)
		cd[--start]='0';
		else
		cd[--start]='1';
		HC[i]=(char *)malloc((n-start)*sizeof(char));
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
	printf("\n");
	for(i=1; i<=n; i++)  
	printf("权重为 %3d 的字符的赫夫曼编码为 %s\n",HT[i].weight,HC[i]);  
}
int Huffmanall()
{
	HuffmanTree HT;
	HuffmanCode HC;
	int *w,i,n,weight;
	printf("\n请输入字符的个数 n= " );
	scanf("%d",&n);
	w=(int *)malloc((n+1)*sizeof(int));
	printf("\n请分别输入%d个字符的权重:\n",n);
	for(i=1;i<=n;i++)
	{
		 printf("%d: ",i);  
		scanf("%d",&weight);
		w[i]=weight;
	}
	HuffmanCoding(HT,HC,w,n);
}
main()
{
	Huffmanall();
}
