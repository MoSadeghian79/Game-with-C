#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct King{
	char name[100];
	int people;
	int court;
	int treasury;
};

struct Solution{
	char text[200];
	int people;
	int court;
	int treasury;
};

struct Problem {
	int number;
	char question[200];
	struct Solution first;
	struct Solution second;
	int repetition;
	struct Problem * next;
};

struct Problem * reach_to_i(struct Problem * dad , int n)
{
	int i;
	struct Problem * tmp;
	tmp = dad;
	for(i=0;i<n;i++)
		tmp = tmp -> next;
	return tmp;
}



void save(int *repetition , int size,struct King king,int condition)
{
	// if condition = 1 => gameover
	FILE * fp;
	int i;
	char filename[100];
	for (i=0;i<strlen(king.name);i++)
		filename[i] = king.name[i];
	filename[strlen(king.name)] = '\0';
	strcat(filename,".txt");
	fp = fopen (filename,"w");
	
	fprintf(fp,"%s\n",king.name);
	fprintf(fp,"%d\n",condition);
	fprintf(fp,"%d\n",king.people);
	fprintf(fp,"%d\n",king.court);
	fprintf(fp,"%d\n",king.treasury);
	for (i=0;i<size;i++)
		fprintf(fp,"%d  ",repetition[i]);
	fclose(fp);
	return ;
	
}

void load_game(struct King * king,int * repetition,int size)
{
	FILE * fp;
	int i,condition;
	char filename[100];
	for (i=0;i<strlen(king->name);i++)
		filename[i] = king->name[i];
	filename[strlen(king->name)] = '\0';
	strcat(filename,".txt");
	fp = fopen (filename,"r");
	fscanf(fp,"%s",&(king->name));
	fscanf(fp,"%d",&(condition));
	if (condition == 0)
	{
		fscanf(fp,"%d",&(king->people));
		fscanf(fp,"%d",&(king->court));
		fscanf(fp,"%d",&(king->treasury));
		for (i=0;i<size;i++)
		{
			fscanf(fp,"%d",(repetition+i));
		}
	}
	fclose(fp);
}

int count_problem()
{
	int count = 0;
	char name[100];
	FILE * file;
	file = fopen("choices.txt","r");
	while ((fscanf(file,"%s",&name)) != EOF)
	{
		count++;	
	}
	fclose(file);
	return count;
}

struct Problem *  create_choice (char file[100])
{
	FILE * choice;
	char bog[100];
	choice = fopen(file,"r");
	struct Problem * problem;
	problem = (struct Problem *) malloc(sizeof(struct Problem));
	fgets(problem -> question,200,choice);
	fgets(problem -> first.text,200,choice);
	fscanf(choice,"%d",&(problem -> first.people));
	fscanf(choice,"%d",&(problem -> first.court));
	fscanf(choice,"%d",&(problem -> first.treasury));
	
	fgets(bog,200,choice);// why god why
	
	fgets(problem -> second.text,200,choice);
	fscanf(choice,"%d",&(problem -> second.people));
	fscanf(choice,"%d",&(problem -> second.court));
	fscanf(choice,"%d",&(problem -> second.treasury));
	problem -> repetition = 3;
	problem -> next = NULL;
	fclose(choice);
	return problem;
}

struct Problem * create_file ()
{
	int count = 0,i;
	char name[100];
	struct Problem * tmp;
	struct Problem * dad;
	FILE * file;
	file = fopen("choices.txt","r");
	while ((fscanf(file,"%s",&name)) != EOF)
	{
		count++;	
	}
	fclose(file);
	file = fopen("choices.txt","r");
	for (i=0;i<count;i++)
	{
		fscanf(file,"%s",name);
		if (i != 0){
			tmp -> next = create_choice(name);
			tmp = tmp -> next;
		}
		if (i == 0){
			tmp = create_choice(name);
			dad = tmp;
		}
		tmp ->number = i;	
		
	}
	fclose(file);
	return dad;
}

void delete_node (struct Problem * dad , int n)
{
	struct Problem * tmp;
	struct Problem * asdf;
	tmp = reach_to_i(dad ,n-1);
	asdf = tmp -> next;
	tmp -> next = asdf -> next;
	free(asdf);
	return ;
}

void delete_end(struct Problem * dad,int n)
{
	struct Problem * tmp;
	tmp = reach_to_i(dad ,n-1);
	free(tmp -> next);
	tmp -> next = NULL;
	return ;
}

void game()
{
	char save_mod;
	int count = count_problem(),mod,i,repetition[count],answer;
	for(i=0;i<count;i++)
		repetition[i] = 3;
	struct King king;
	struct King * pking;
	printf("Enter your name:");
	scanf("%s",king.name);
	king.people = 50;
	king.court = 50;
	king.treasury =50;
	pking  = &king;
	printf("Welcome %s, select one of these options:\n",king.name);
	printf("[1]new game\n");
	printf("[2]load game\n");
	scanf("%d",&mod);	
	if (mod == 2)
		load_game(pking,repetition,count);

	struct Problem * dad;
	struct Problem * tmp;
	struct Problem * end;
	dad = create_file ();
	
	while (1)
	{
		printf("people: %d  ",king.people);
		printf("court: %d  ",king.court);
		printf("treasury: %d  \n",king.treasury);
		
		// questions
		srand(time(NULL));
		int random = rand() %  count;
		tmp = reach_to_i(dad , random);
		printf("%s\n",tmp->question);
		printf("[1]%s\n",tmp->first.text);
		printf("[2]%s\n",tmp->second.text);
		scanf("%d",&answer);
		if (answer == 1)
		{
			king.people += tmp -> first.people;
			king.court += tmp ->first.court;
			king.treasury += tmp ->first.treasury;
		}
		else if (answer == 2) 
		{
			king.people += tmp -> second.people;
			king.court += tmp ->second.court;
			king.treasury += tmp ->second.treasury;
		}
		if (answer == -1)
		{
			printf("Do you want to save your game\n");
			scanf("%s",&save_mod);
			if (save_mod == 'y')
				save(repetition,count_problem(),king,0);
			return ;
		}
		tmp -> repetition --;
		repetition[tmp -> number] --;
		
		
		// for delete node
		if (repetition[tmp -> number] == 0)
		{
			if(random == 0 && count > 1)
				dad = dad -> next;
			else if (random == 0 && count == 1)
				{
					end = create_file ();
					dad = end;
					count = count_problem()+1;
					for(i=0;i<count-1;i++)
						repetition[i] = 3;
				}
			else if ((random > 0) && (random <(count-1)) && count > 2) 
				delete_node(dad , random);
			count --;	
		}
		
		// if king lose game
		if ((king.people <= 0 ) || (king.court <= 0 ) 
		|| (king.treasury <= 0 ) || (king.people+king.court+king.treasury) < 30)
		{
			printf("\n You lose \n\n");
			printf("Do you want to save your game\n");
			scanf("%s",&save_mod);
			if (save_mod == 'y')
				save(repetition,count_problem(),king,1);
			return ;
		}
		
		// if overflow
		if (king.people > 100)
			king.people =100;
		if (king.court > 100)
			king.court =100;
		if (king.treasury > 100)
			king.treasury =100;
			
	}
}

int main(int argc, char *argv[]) {

	game();

	return 0;
}
