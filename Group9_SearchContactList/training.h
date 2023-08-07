#pragma once

// HMM_P1.cpp : Defines the entry point for the console application.
//

long double Aij[1000][1000];	//2D array to store the A matrix
long double Bjk[1000][1000];	//2D array to store B matrix
long double pi[1000];			//2D array to store pi matrix
long double Aij_compliment[1000][1000];
long double Bjk_compliment[1000][1000];
long double pi_compliment[1000];
int observations[1000];
long double alpha[100000][100];
long double beta[100000][100];
long double gamma[100000][100];
long double delta[100000][100];
long double xi[1000][100][100];
int psi[100000][100];

int digit_no=1;
int file_no = 1;
int N = 5;
int T;
long double Pstar = 0.0;
int Qstar[1000];

//Function to read A matrix from text file
int read_Aij(int digit)
{
	char filename[60];
	sprintf(filename,"models/%d/A.txt",digit);
	FILE *fptr = fopen(filename, "r");
	for(int i = 1; i<=N; i++)
	{
		for(int j = 1; j<=N; j++)
		{
			fscanf(fptr,"%Lf",&Aij[i][j]);
		}
	}
	fclose(fptr);
	return 0;
}

//function to read B matrix from text file
int read_Bjk(int digit)
{
	char filename[60];
	sprintf(filename,"models/%d/B.txt",digit);
	FILE *fptr = fopen(filename, "r");
	for(int i = 1; i<=N; i++)
	{
		for(int j = 1; j<=M; j++)
		{
			fscanf(fptr,"%Lf",&Bjk[i][j]);
		}
	}
	fclose(fptr);
	return 0;
}

//function to read pi matrix from text file
int read_pi(int digit)
{
	char filename[60];
	sprintf(filename,"models/%d/pi.txt",digit);
	FILE *fptr = fopen(filename, "r");
	for(int i = 1; i<=N; i++)
	{
		fscanf(fptr,"%Lf",&pi[i]);
	}
	fclose(fptr);
	return 0;
}

//function to read codebook from text file
int read_codebook()
{
	int row = 0;
	FILE *fptr = fopen("codebook.csv","r");
	for(int i = 1; i<=M; i++)
	{
		for(int j = 1; j<=P; j++)
		{
			fscanf_s(fptr,"%Lf,",&codebook[i][j]);
		}
	}
	codebook_size = M;
	return 0;
}

//function to generate the observation sequence of the given data
int generate_observation_sequence(char *filename)
{
	int n;
	long double distortion;
	read_file(filename);
	data_framing();
	T = frame;
	for(int i = 1; i<=frame; i++)
	{
		Ri_calculator(framed_data[i]);
		Ai_calculator();
		Ci_calculator();
		n = tokhura_distance(C,distortion);
		observations[i] = n;
	}
	return 0;
}

//function to implement backward procedure and generate beta matrix
int backward_procedure()
{
	for(int i = N; i<= N; i++)
	{
		beta[T][i] = 1;
	}
	for(int i = T-1; i>0; i--)
	{
		for(int j = 1; j<= N; j++)
		{
			long double n = 0;
			for(int k = 1; k<= N; k++)
			{
				n += Aij[j][k] * Bjk[k][observations[i+1]] * beta[i+1][k];
			}
			beta[i][j] = n;
		}
	}
	return 0;
}

//function to implement forward procedure and to generate alpha matrix
long double forward_procedure()
{
	for(int i = 1; i<= N; i++)
	{
		alpha[1][i] = pi[i] * Bjk[i][observations[1]];
	}
	for(int i = 2; i<= T; i++)
	{
		for(int j = 1; j<= N; j++)
		{
			long double n = 0;
			for(int k = 1; k<= N; k++)
			{
				n += alpha[i-1][k] * Aij[k][j];
			}
			alpha[i][j] = n*Bjk[j][observations[i]];
		}
	}
	long double probability = 0;
	//loop to find the probability P(O/Lambda)
	for(int i = 1; i<=N; i++)
	{
		probability += alpha[T][i];
	}
	return probability;
}

//function to implement viterbi algorithm and find P* and state sequence
int viterbi()
{
	for(int i = 1; i<=N; i++)
	{
		delta[1][i] = pi[i]*Bjk[i][observations[1]];
		psi[1][i] = 0;
	}
	for(int t = 2; t<=T; t++)
	{
		int state = 0;
		for(int j = 1; j<=N; j++)
		{
			long double max = 0;
			long double arg_max = 0;
			for(int i = 1; i<=N; i++)
			{
				long double var;
				var = delta[t-1][i] * Aij[i][j];
				if(arg_max < var)
				{
					arg_max = var;
					state = i;
				}
				var = var * Bjk[j][observations[t]];
				if(max < var)
					max = var;
			}
			delta[t][j] = max;
			//printf("%E ",delta[t][j]);
			psi[t][j] = state;
		}
		//printf("\n");
	}
	long double max = 0;
	int state;
	for(int i = 1; i<=N; i++)
	{
		if(max < delta[T][i])
		{
			max = delta[T][i];
			state = i;
		}
	}
	Pstar = max;
	Qstar[T] = state;
	//printf("P* : %E\n",Pstar);
	//printf("QT* : %d\n",Qstar[T]);
	for(int t = T-1; t>0; t--)
	{
		Qstar[t] = psi[t+1][Qstar[t+1]];
	}
	/*printf("\nState sequence using Viterbi algorithm :\n");
	for(int i = 1; i<=T; i++)
		printf("%d ",Qstar[i]);
	printf("\n");*/
	return 0;
}

//function to implement solution to problem 2 and find the gamma matrix
int problem2()
{
	for(int i = 1; i<=T ; i++)
	{
		for(int j = 1; j<=N; j++)
		{
			long double n = 0;
			for(int k = 1; k<=N; k++)
			{
				n += alpha[i][k] * beta[i][k];
			}
			gamma[i][j] = (alpha[i][j] * beta[i][j])/n;
		}
	}
	long double max = 0;
	int state;
	for(int i = 1; i<=T; i++)
	{
		max = 0;
		for(int j = 1; j<=N; j++)
		{
			if(max < gamma[i][j])
			{
				max = gamma[i][j];
				state = j;
			}
		}
	}
	viterbi();
	return 0;
}

//function to re-estimate the model
int problem3()
{
	long double a,b;
	for(int t=1;t<=T-1;t++)
	{
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=N;j++)
			{
				a=alpha[t][i]*Aij[i][j]*Bjk[j][observations[t+1]]*beta[t+1][j];
				b=0;
				for(int l=1;l<=N;l++)
				{
					for(int m=1;m<=N;m++)
					{
						b += alpha[t][l]*Aij[l][m]*Bjk[m][observations[t+1]]*beta[t+1][m];
					}
				}
				xi[t][i][j]=a/b;
			}
		}
	}
	long double max = 0, sum = 0;
	int x;
	for(int i=1;i<=N;i++)
	{
		pi[i]=gamma[1][i];
		sum += pi[i];
		if(max < pi[i])
		{
			max = pi[i];
			x = i;
		}
	}
	pi[x] = pi[x] + 1 - sum;
	for(int i=1;i<=N;i++)
	{
		sum = 0;
		max = 0;
		for(int j=1;j<=N;j++)
		{
			a=0,b=0;
			for(int t=1;t<=T-1;t++)
			{
				a += xi[t][i][j];
				b+=gamma[t][i];
			}
			Aij[i][j]= a/b;
			sum += Aij[i][j];
			if(max < Aij[i][j])
			{
				x = j;
				max = Aij[i][j];
			}
		}
		Aij[i][x] = Aij[i][x] + 1 - sum;
	}
	for(int j=1;j<=N;j++)
	{
		b=0;
		sum = 0;
		max = 0;
		for(int t=1;t<=T;t++)
		{
			b+=gamma[t][j];
		}
		for(int k=1;k<=M;k++)
		{
			a=0;
			for(int t=1;t<=T;t++)
			{
				if(observations[t]==k)
					a +=gamma[t][j];
			}
			Bjk[j][k]= a/b;
			if(Bjk[j][k] < 1e-30) Bjk[j][k] = 1e-30;
			sum += Bjk[j][k];
			if(max < Bjk[j][k])
			{
				x = j;
				max = Bjk[j][k];
			}
		}
		Bjk[j][x] = Bjk[j][x] + 1 - sum;
	}
	return 0;
}

//function to find the average of all the models of a particular digit
int model_averager()
{
	for(int i =1; i<=N; i++)
	{
		pi_compliment[i] += pi[i];
	}
	for(int i = 1; i<=N; i++)
	{
		for(int j =1; j<=N;j++)
		{
			Aij_compliment[i][j] += Aij[i][j];
		}
	}
	for(int i = 1; i<=N; i++)
	{
		for(int j = 1; j<=M; j++)
		{
			Bjk_compliment[i][j] += Bjk[i][j];
		}
	}
	return 0;
}

//function to initialize the model to 0.
int set_zero()
{
	for(int i =1; i<=N; i++)
	{
		pi[i] = 0;
		pi_compliment[i] = 0;
	}
	for(int i = 1; i<=N; i++)
	{
		for(int j =1; j<=N;j++)
		{
			Aij[i][j] = 0;
			Aij_compliment[i][j] = 0;
		}
	}
	for(int i = 1; i<=N; i++)
	{
		for(int j = 1; j<=M; j++)
		{
			Bjk[i][j] = 0;
			Bjk_compliment[i][j] = 0;
		}
	}
	return 0;
}

//function to initialize the model for the first iteration
int initialize_model()
{
	for(int i =1; i<=N; i++)
	{
		if(i==1) pi[i] = 1;
		else
			pi[i] = 0;
	}
	for(int i = 1; i<=N; i++)
	{
		for(int j =1; j<=N;j++)
		{
			if(i==N)
			{
				if(j==N)	Aij[i][j] = 1;
				else	Aij[i][j] = 0;
			}
			else
			{
				if(i==j) Aij[i][j] = 0.8;
				else if(i+1 == j) Aij[i][j] = 0.2;
				else Aij[i][j] = 0;
			}
		}
	}
	for(int i = 1; i<=N; i++)
	{
		for(int j = 1; j<=M; j++)
		{
			Bjk[i][j] = 1.0/M;
		}
	}
	return 0;
}

//function to read the model from the text file
int read_model(int digit)
{
	read_Aij(digit);
	read_Bjk(digit);
	read_pi(digit);
	return 0;
}

//function to print the model in text files
int print_model(int digit)
{
	char filename[60];
	sprintf(filename,"models/%d/pi.txt",digit);
	FILE *fptr = fopen(filename, "w");
	for(int i =1; i<=N; i++)
	{
		fprintf(fptr,"%.12E ",pi_compliment[i]/input_files);
	}
	fclose(fptr);
	fflush(fptr);
	sprintf(filename,"models/%d/A.txt",digit);
	fptr = fopen(filename, "w");
	for(int i = 1; i<=N; i++)
	{
		for(int j =1; j<=N;j++)
		{
			fprintf(fptr,"%.12E ",Aij_compliment[i][j]/input_files);
		}
		fprintf(fptr,"\n");
	}
	fclose(fptr);
	fflush(fptr);
	sprintf(filename,"models/%d/B.txt",digit);
	fptr = fopen(filename, "w");
	for(int i = 1; i<=N; i++)
	{
		for(int j = 1; j<=M; j++)
		{
			fprintf(fptr, "%.12E ",Bjk_compliment[i][j]/input_files);
		}
		fprintf(fptr,"\n");
	}
	fclose(fptr);
	fflush(fptr);
	return 0;
}

//function to generate the trained model for each digit;
int training()
{
	printf("\n\nTraining Models");
	read_codebook();
	for(int i = 0; i<digits; i++)
	{
		for(int j = 1; j<=3; j++)
		{
			set_zero();
			printf("-");
			for(int k = 1; k<= input_files; k++)
			{
				char filename[60];
				sprintf_s(filename,"Data/224101010_E_%d_%d.txt",i,k);
				generate_observation_sequence(filename);
				long double Pstar_old;
				if(j==1)
					initialize_model();
				else
					read_model(i);
				Pstar = 1e-300;
				int count = 0;
				do
				{
					count++;
					Pstar_old = Pstar;
					forward_procedure();
					backward_procedure();
					problem2();
					problem3();
				}
				while((Pstar_old/Pstar) < 1 && count < 1000);
				model_averager();
			}
			print_model(i);
		}
	}
	system("cls");
	printf("\nModels were successfully trained.\n");
	return 0;
}

int train_model()
{
	create_universe();
	generate_codebook();
	training();
	return 1;
}