#pragma once
const int P = 12;	//Number of cepstral coefficients
const int M = 32;	//final size of the codebook
const long double del = 0.00001;	//value of delta
const long double epsilon = 0.03;	

const int D = 320;  //variable to store number of data samples in each frame
const int scaling_factor = 5000;  //variable to store scaling factor
const int digits = 10;	//Number of digits ,i.e, 0 to 9
const int input_files = 20;	//Number of files that are used for training.
const int testing_files = 10;	//Number of files that are used for testing


long double data[100000];	//Array to store the data
long double framed_data[1000][D+1];	//2D array to store the framed data
long double R[P+1], A[P+1], C[P+1];	//Arrays to store the value of Ri's, Ai's and cepstral coefficients
int frame = 0;	//variable to store number of frames of data stored in framed_data array
int data_size;	//variable to store the number of data points stored in data array


long double tokhuraWeights[] = {1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};
int universe_size ;		//variable to store the size of universe data
int codebook_size;	//variable to store current size of the codebook
int count = 0;	//variable to store the total number of times K-Means algorithm is executed
int LBG_count = 0;	//variable to store the total number of times LBG algorithm is executed
long double codebook[M+1][P+1];	//matrix to store the codebook
long double cluster[M + 1][P+1];	//matrix to store the clusters


//hamming_window : function to apply hamming window to each frame
int hamming_window(long double data[])
{
	long double w;
	for(int i = 0; i < D; i++)
	{
		w = 0.54 - 0.46 * cos((2 * (22.0/7.0) * i)/(D-1));
		data[i] = w * data[i];
	}
	return 0;
}

//sine_liftering: function to apply liftering to the cepstral coefficients
int sine_liftering()
{
	for(int i = 1; i<=P; i++)
	{
		C[i] = C[i]*(1 + (P/2) * sin((22.0/7.0) * i/P)); 
	}
	return 0;
}


//normalize_data : function to normalize the input voice data of a vowel file
int normalize_data()
{
	long double max_value = 0;
	//loop to find maximum value in the data
	for(int i = 0; i < data_size; i++)
	{
		if(data[i] < 0 && -1*data[i] > max_value)
			max_value = -1*data[i];
		else if(data[i] >= 0 && data[i] > max_value)
			max_value = data[i];
	}
	//loop for data normalization
	for(int i = 0; i < data_size; i++)
	{
		data[i] = data[i] * ((long double)scaling_factor/max_value);
	}
	return 0;
}

//dc_shift : function to remove the DC shift from the data
int dc_shift()
{
	long double DCshift = 0;
	for(int i = 0; i < data_size; i++)
	{
		DCshift += data[i];
	}
	DCshift /= data_size;
	//for loop to subtract DC shift from each of the amplitude values
	for(int i = 0; i < data_size; i++)
	{
		data[i] = data[i] - DCshift;
	}
	return 0;
}

//Ri_calculator : function to calculate and store the values of auto correlations.
int Ri_calculator(long double input_data[])
{
	for(int lag = 0; lag <= P; lag++)
	{
		R[lag] = 0;
		for(int i = 0; i+lag < D; i++)
		{
				R[lag] = R[lag] + input_data[i]*input_data[i+lag];
		}
	}
	return 0;
}
//Ai_calculator : function to calculate and store the LPC coefficients for each frame.
int Ai_calculator()
{
	long double E[P + 1];
	long double k[P+1];
	long double alpha[P+1][P+1];
	long double value;
	E[0]= R[0];
	for(int i = 1; i<= P; i++)
	{
		value = 0;
		for(int j = 1; j < i; j++)
		{
			value = value + alpha[j][i-1] * R[i-j];
		}
		k[i] = (R[i] - value)/E[i-1];
		alpha[i][i] = k[i];
		for(int j = 1; j < i; j++)
		{
			alpha[j][i] = alpha[j][i-1] - k[i] * alpha[i-j][i-1];
		}
		E[i] = (1 - k[i]*k[i]) * E[i-1];
	}
	//loop to store the values of LPC coefficients.
	for(int i = 1;i <= P; i++)
	{
		A[i] = alpha[i][P];
	}
	return 0;
}

//Ci_calculator : function to calculate the cepstral coefficients using LPC coefficients for each frame
int Ci_calculator()
{
	long double value;
	for(int i = 1; i <= P; i++)
	{
		if(i<=P)
		{
			value = 0;
			for(int j = 1; j<=i-1; j++)
			{
				value = value + ((long double)j/(long double)i) * C[j] * A[i-j];
			}
			C[i] = A[i] + value;
		}
	}
	sine_liftering();
	return 0;
}

//read_file : function to read data from the file, store it in an array and also apply dc shift and normalization on the stored data
int read_file(char *filename)
{
	FILE *fptr;
	long double n;
	data_size = 0;
	if(fptr = fopen(filename, "r"))
	{
		while(fscanf_s(fptr,"%Lf",&n) != EOF)
		{
			data_size++;
			data[data_size] = n;
		}
	}
	fclose(fptr);
	dc_shift();
	normalize_data();
	return 0;
}
/*
	data_framing : This function is used to extract frames of data and store it in framed data array.
					The frame window shifts by 80 on every iteration ,i.e, if a frame starts from ith index then
					the next frame will start from (i+80)th index of data array
*/
int data_framing()
{
	frame = 0;
	int j = 0;
	for(int i = 1; i+320<=data_size; i +=80)
	{
		frame++;
		for(int j = i; j<=i+320-1; j++)
		{
			framed_data[frame][j-i+1] = data[j];
		}
	}
	for(int i = 1; i<=frame; i++)
	{
		hamming_window(framed_data[i]);
	}
	return 0;
}

/*create_universe : this function is used to generate universe data needed for LBG algorithm and store it in file universe.csv.
					Function takes frame wise data, calculates its cepstral coefficient and dumps these coefficients in universe.csv file.
*/

int create_universe()
{
	printf("\n\nCreating Universe data");
	FILE *fptr = fopen("universe.csv","w");
	for(int i = 0; i<digits; i++)
	{
		printf("-");
		for(int j = 1; j<=input_files; j++)
		{
			char filename[60];
			sprintf_s(filename,"Data/224101010_E_%d_%d.txt",i,j);
			read_file(filename);
			data_framing();
			for(int k = 1; k<=frame; k++)
			{
				Ri_calculator(framed_data[k]); //function call to calculate Ri's
				Ai_calculator();	//function call to calculate lpc coefficients
				Ci_calculator();	//function call to calculate cepstral coefficients
				//loop to dump cepstral coefficients in universe.csv file
				for(int x = 1; x<=P; x++)
				{
					fprintf_s(fptr,"%Lf,",C[x]);
				}
				fprintf_s(fptr,"\n");
			}
		}
	}
	fclose(fptr);
	fflush(fptr);
	system("cls");
	printf("\nData Universe successfully created.\n");
	return 0;
}

/* find_universe_size : function to find the size of universe data present in universe.csv file
*/

int find_universe_size()
{
	FILE *fptr;
	int r = 0;
	long double n;
	if(fptr = fopen("Universe.csv","r"))
	{
		while(fscanf_s(fptr,"%Lf,",&n)!=EOF)
		{
			r++;
		}
		universe_size = r/P;
	}
	return 0;
}

/*tokhura_distance : function to calculate average tokhura distance between the codebook vector and given universe data for a particular file
					 and return the index of the code vector which is at minimum distance from the given data point.
*/
int tokhura_distance(long double data[], long double &distortion)
{
	long double min = 99999,dist;
	int ans;
	for(int j = 1; j<=codebook_size; j++)
	{
		dist = 0;
		for(int k = 1; k<=P; k++)
		{
			long double d = data[k] - codebook[j][k];
			dist += tokhuraWeights[k-1]*d*d;
		}
		if(min > dist)
		{
			ans = j;
			min = dist;
		}
	}
	distortion += min;
	return ans;
}

//print_final_codebook : function to print the final codebook in TXT file
int print_final_codebook()
{
	FILE *fptr;
	codebook_size /=2;
	fptr = fopen("codebook.csv","w");
	for(int i = 1;i<=M; i++)
	{
		for(int j = 1; j<=P; j++)
		{
			fprintf(fptr,"%Lf,",codebook[i][j]);
		}
		fprintf(fptr,"\n");
	}
	return 0;
}

//KMeans : function to run KMeans algorithm till the average distortion is less than delta
int KMeans(long double &distortion)
{
	long double previous_distortion = 0;
	distortion = 99999;
	long double dis = 9999;
	long double data[P+1]; 
	int KMeans_count = 0;
	for(int i = 1;i<=codebook_size; i++)
	{
		for(int j = 0; j<=P; j++)
		{
			cluster[i][j] = 0;
		}
	}
	while(dis > del)
	{
		FILE *fptr = fopen("universe.csv","r");
		count++;
		KMeans_count++;
		previous_distortion = distortion;
		distortion = 0;
		//loop to iterate over the universe data
		for(int i = 1;i<=universe_size; i++)
		{
			for(int j = 1; j<=P; j++)
			{
				fscanf_s(fptr,"%Lf,",&data[j]);
			}
			int n = tokhura_distance(data,distortion); // n: index of codevector which is at minimum distance from data 'i'
			cluster[n][0]++;	//incrementing the number of data points in cluster 'n'
			for(int j = 1; j<=P; j++)
			{
				cluster[n][j] += data[j];
			}
		}
		fclose(fptr);
		//updataing the codebook with new code vectors
		for(int i = 1;i<=codebook_size; i++)
		{
			codebook[i][0] = cluster[i][0];
			if(codebook[i][0] != 0)
			{
				for(int j = 1; j<=P; j++)
				{
					codebook[i][j] = cluster[i][j]/cluster[i][0] ;
					cluster[i][j] = 0;
				}
			}
			cluster[i][0] = 0;
		}
		distortion /= universe_size;
		dis = previous_distortion - distortion;	//difference between current and previous distortions
		if(dis < 0) dis *= -1;
	}
	return 0;
}

//LBG : function to run LBG algorithm
int LBG()
{
	codebook_size = 1; //initializing the codebook size with 1.
	long double a;
	count = 0;
	long double distortion;
	while(codebook_size <= M)
	{
		printf("-");
		LBG_count++;
		KMeans(distortion);	//function call to inplement KMeans algorithm using codebook of given size
		//splitting the codebook
		if(codebook_size < M)
		{
			for(int i = 1; i<=codebook_size; i++)
			{
				for(int j = 1; j<=P; j++)
				{
					a = codebook[i][j];
					codebook[i][j] = a*(1+epsilon);
					codebook[i+codebook_size][j] = a*(1-epsilon);
				}
			}
		}
		codebook_size *= 2;	//increasing the codebook size to twice the current size.
	}
	print_final_codebook(); //function call to print the final generated codebook in TXT file
	return 0;
}
int generate_codebook()
{
	printf("\n\nGenerating Codebook");
	find_universe_size();
	LBG();	//function call to implement LBG algorithm
	system("cls");
	printf("\nCodebook was successfully generated.\n");
	return 0;
}
