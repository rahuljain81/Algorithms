#include <malloc.h>
#define MAX_ID            100
#define MAX_CHILD		  50	

#define MAX_STR_LENGTH    3000
#define MAX_IMAGE_HEIGHT  50
#define MAX_IMAGE_WIDTH   50

#define MAX_SCREEN_HEIGHT 1000
#define MAX_SCREEN_WIDTH  1000

enum Type {
	VWIDGET = 0,
	HWIDGET,
	TEXT,
	IMAGE,
};

typedef struct {
	int type;
	union {
		struct { int width; } vwidget;
		struct { int height; } hwidget;
		struct { char *strPtr; } text;
		struct { int height, width; char *imagePtr; } image;
	};
} Element;

typedef struct 
{
	int height, width;	
}vwidget;
typedef struct
{
	int height, width;	
}hwidget;
typedef struct
{
	char strPtr[MAX_STR_LENGTH];
	int len;
}text;
typedef struct
{
	int height, width;
	char imagePtr[MAX_IMAGE_HEIGHT][MAX_IMAGE_WIDTH];
}image;

typedef struct 
{
	int type;
	vwidget V;
	hwidget H;
	text T;
	image I;
	int child[MAX_CHILD];
	int childcount;
} MyElement;

MyElement arr[MAX_ID];

int count = 0;

void init()
{
	count = 0;
};

int  create(Element* elementPtr)
{
	switch (elementPtr->type)
	{
		case VWIDGET:
		{
			MyElement* v = &arr[count++];
			v->type = elementPtr->type;
			v->V.width = elementPtr->vwidget.width;
			v->V.height = 0;
			v->childcount = 0;
			break;
		}
		case HWIDGET:
		{
			MyElement* h = &arr[count++];
			h->type = elementPtr->type;
			h->H.height = elementPtr->hwidget.height;
			h->H.width = 0;
			h->childcount = 0;
			break;
		}
		case TEXT:
		{
			int i, j;
			MyElement* T = &arr[count++];
			T->type = elementPtr->type;
			i = 0;
			while (elementPtr->text.strPtr[i] != '\0')
				i++;
			for (j = 0; j < i; j++)
				T->T.strPtr[j] = elementPtr->text.strPtr[j];
			T->T.len = i;
			break;
		}
		case IMAGE:
		{
			int i, j;
			MyElement* T = &arr[count++];
			T->type = elementPtr->type;
			T->I.height = elementPtr->image.height;
			T->I.width = elementPtr->image.width;
			for (i = 0; i < T->I.height; i++)
				for (j = 0; j < T->I.width; j++)
					T->I.imagePtr[i][j] = elementPtr->image.imagePtr[i * T->I.width + j];
			break;
		}
		default:
			break;
	}
	return count - 1;
}
void add(int parentId, int childId)
{
	MyElement* p = &arr[parentId];
	p->child[p->childcount] = childId;
	p->childcount++;
	return;
}
int getwidth(int id, int option_height);

int getheight(int id, int option_width)
{
	int i;
	MyElement* p = &arr[id];
	int maxh= 0;
	int tmp;
	switch (p->type)
	{
		case VWIDGET:
		{
			int localmaxw = p->V.width - 2;
			int localmaxh = p->V.height;
			for (i = 0; i < p->childcount; i++)
			{
				tmp = getwidth(p->child[i], -1);
				if (tmp > localmaxw)
					localmaxw = tmp;
			}
			tmp = 0;
			for (i = 0; i < p->childcount; i++)			
				tmp += getheight(p->child[i], localmaxw);				
			
			p->V.width = localmaxw + 2;
			p->V.height = (tmp > 0)? tmp: localmaxh;
			p->V.height += 2;
			if (p->V.height > maxh)
				maxh = p->V.height;
			break;
		}
		case HWIDGET:
		{
			int localmaxh = p->H.height - 2;
			for (i = 0; i < p->childcount; i++)
			{
				tmp = getheight(p->child[i], -1);
				if (tmp > localmaxh)
					localmaxh = tmp;
			}
			p->H.height = localmaxh + 2;
			if (p->H.height > maxh)
				maxh = p->H.height;
			break;
		}
		case TEXT:
		{
			if (option_width != -1)
			{
				int rem = p->T.len % option_width;
				int ques = p->T.len / option_width;
				if (rem != 0)
					ques += 1;
				if (ques > maxh)
					maxh = ques;
			}
			break;
		}
		case IMAGE:
		{
			if (p->I.height > maxh)
				maxh = p->I.height;
			break;
		}
	}
	return maxh;
}

int getwidth(int id, int option_height)
{
	int i;
	MyElement* p = &arr[id];
	int maxw = 0;
	int tmp;
	switch (p->type)
	{
		case VWIDGET:
		{
			int localmaxw = p->V.width - 2;			
			for (i = 0; i < p->childcount; i++)
			{
				tmp = getwidth(p->child[i], -1);
				if (tmp > localmaxw)
					localmaxw = tmp;
			}
			p->V.width = localmaxw + 2;
			if (p->V.width > maxw)
				maxw = p->V.width;
			break;
		}
		case HWIDGET:
		{			
			int localmaxh = p->H.height - 2;
			int localmaxw = p->H.width;
			for (i = 0; i < p->childcount; i++)
			{
				tmp = getheight(p->child[i], -1);
				if (tmp > localmaxh)
					localmaxh = tmp;
			}
			tmp = 0;
			for (i = 0; i < p->childcount; i++)			
				tmp += getwidth(p->child[i], localmaxh);

			p->H.width = (tmp > 0) ? tmp : localmaxw;
			p->H.width += 2;
			p->H.height = localmaxh + 2;
			if (p->H.width > maxw)
				maxw = p->H.width;			
			break;
		}
		case TEXT:
		{
			if (option_height != -1)
			{
				int rem = p->T.len % option_height;
				int ques = p->T.len / option_height;
				if (rem != 0)
					ques += 1;
				if (ques > maxw)
					maxw = ques;
			}
			break;
		}
		case IMAGE:
		{
			if (p->I.width > maxw)
				maxw = p->I.width;
			break;
		}
	}
	return maxw;
}

void print(char screen[MAX_SCREEN_HEIGHT][MAX_SCREEN_WIDTH], int id, int startx, int starty, int height, int width, int first)
{
	MyElement* p = &arr[id];
	int i, j;

	if (first)
	{
		for (i = 0; i < height; i++)
			for (j = 0; j < width; j++)
				screen[startx + i][starty + j] = ' ';
	}

	if (p->type == VWIDGET || p->type == HWIDGET)
	{
		for (i = 0; i < height; i++)
		{
			screen[startx + i][starty + 0] = '+';
			screen[startx + i][starty + width - 1] = '+';
		}
		for (i = 0; i < width; i++)
		{
			screen[startx + 0][starty + i] = '+';
			screen[startx + height - 1][starty + i] = '+';
		}
	}

	startx++;
	starty++;
	switch (p->type)
	{
		case VWIDGET:
		{
			int localstartx = startx;
			int localstarty = starty;
			for (int ii = 0; ii < p->childcount; ii++)
			{
				MyElement* c = &arr[p->child[ii]];
				switch (c->type)
				{
					case VWIDGET:
						print(screen, p->child[ii], localstartx, localstarty, c->V.height, c->V.width, 0);
						localstartx += c->V.height;
						c->V.height = 0;
						break;
					case HWIDGET:
						print(screen, p->child[ii], localstartx, localstarty, c->H.height, c->H.width, 0);
						localstartx += c->H.height;
						c->H.width = 0;
						break;
					case TEXT:
					{
						int ques = c->T.len / p->V.width;
						int remainder = c->T.len % p->V.width;
						for (int i = 0; i < ques; i++)
							for (int j = 0; j < p->V.width; j++)
								screen[localstartx + i][localstarty + j] = c->T.strPtr[i * p->V.width + j];
						localstartx += ques;
						if (remainder)
						{
							for (int i = 0; i < remainder; i++)
								screen[localstartx + 1][localstarty + i] = c->T.strPtr[ques * p->V.width + i];
							localstartx += 1;
						}
						break;
					}
					case IMAGE:
					{
						int i, j;
						for (i = 0; i < c->I.height; i++)
							for (j = 0; j < c->I.width; j++)
								screen[localstartx + i][localstarty + j] = c->I.imagePtr[i][j];
						localstartx += c->I.height;
						break;
					}
				}
			}
			break;
		}
		case HWIDGET:
		{
			int localstartx = startx;
			int localstarty = starty;
			for (int ii = 0; ii < p->childcount; ii++)
			{
				MyElement* c = &arr[p->child[ii]];
				switch (c->type)
				{
					case VWIDGET:
						print(screen, p->child[ii], localstartx, localstarty, c->V.height, c->V.width, 0);
						localstarty += c->V.width;
						c->V.height = 0;
						break;
					case HWIDGET:
						print(screen, p->child[ii], localstartx, localstarty, c->H.height, c->H.width, 0);
						localstarty += c->H.width;
						c->H.height = 0;
						break;
					case TEXT:
					{
						int ques = c->T.len / p->H.height;
						int remainder = c->T.len % p->H.height;
						for (int i = 0; i < ques; i++)
							for (int j = 0; j < p->H.height; j++)
								screen[localstartx + j][localstarty + i] = c->T.strPtr[i * p->H.height + j];
						localstarty += ques;
						if (remainder)
						{							
							for (int i = 0; i < remainder; i++)
								screen[localstartx + i][localstarty] = c->T.strPtr[ques * p->H.height + i];
							localstarty += 1;
						}
						break;
					}
					case IMAGE:
					{
						for (i = 0; i < c->I.height; i++)
							for (j = 0; j < c->I.width; j++)
								screen[localstartx + i][localstarty + j] = c->I.imagePtr[i][j];
						localstarty += c->I.width;
						break;
					}
				}
			}
			break;
		}
	}
}

void show(int elementId, char screen[MAX_SCREEN_HEIGHT][MAX_SCREEN_WIDTH])
{
	int width = getwidth(elementId, -1);
	int height = getheight(elementId, -1);
	print(screen, elementId, 0, 0, height, width, 1);
	return;
}