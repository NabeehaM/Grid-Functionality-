#include <iostream>
#include <fstream>
using namespace std;


//Header Functions for Make_Grid()

int Grid_Dimensions_X; //Holds The Rows of Word Search
int Grid_Dimensions_Y; //Holds the Cols of the Word Search
int Word_X = 0; //Current Word being placed

char* GetStringFromBuffer(char* buffer)
{
	//Calculate the Length of the buffer
	int Len = strlen(buffer);
	char* str = 0;

	//Create a New Array on the Heap and Copy the contents of buffer into it
	if (Len > 0)
	{	
		str = new char[Len + 1]; //1 more for null
		int i = 0;
		for (i = 0 ; buffer[i]!='\0' ; i++)
		{
			str[i] = buffer[i];
		}
		str[i] = '\0';
	}
	return str;
}

//This Function will Read the words File & allocate memory on the heap as a 2D Array
void Allocate_Memory (ifstream &FIN, char ** &WPtr, int &Test_Cases)
{	
	char Temp_Buffer[40]; //Assuming 1 Word is of maximum 40 char in length

	WPtr = new char * [Test_Cases];

	//there are NO garbage values to be read
	//FIN.getline(Temp_Buffer,40); //reads garbage values

	/*cout<<"\nTemp = "<<Temp_Buffer<<endl;
	cout<<"\nNow: \n";*/

	//cout << "test cases = "<<Test_Cases<<endl;
	for (int i = 0; i < Test_Cases; i++) 
	{
		FIN.getline(Temp_Buffer,40);
		//cout<<"\nTemp_Buffer = "<<Temp_Buffer<<endl;
		//cout<<"\nAllocating Space: \n";
		int Len = strlen(Temp_Buffer) + 1;

		WPtr[i] = new char [Len];
		//cout << "Len = "<<Len<<endl;

		WPtr[i] = GetStringFromBuffer(Temp_Buffer); 
		//cout << "Word "<<i<<": "<<WPtr[i]<<endl;

	}

	/*cout<<"\nThe Words are: \n";
	for (int j = 0; j < 10; j++)
		cout<<j<<" "<<WPtr[j]<<endl;*/

	/*cout<<"\nDeAllocating: \n";
	for (int j = 0; j < i; j++)
		delete [] WPtr[j];
	delete []WPtr;*/
}

//This Function will Free Up Space on the Heap
void DeAllocate_Memory (char **&Array, int n)
{
	for (int i = 0; i < n; i++)
		delete [] Array[i];
	delete [] Array;
}

//this function simply swaps its given rows
void Interchange_Words( char* &row1, char* &row2)
{
	char * temp = row1 ;
	row1 = row2;
	row2 = temp; 
}

//This Function will Sort the original list based on ascending order of their lengths
void Sort_List (char **Word_List, const int &Test_Cases)
{
	for (int i = 0; i < Test_Cases - 1; i++)
	{
		for (int j = 0; j < Test_Cases -i - 1; j++)
		{
			if (strlen(Word_List[j]) > strlen(Word_List[j+1]))
				Interchange_Words(Word_List[j],Word_List[j+1]);
		}
	}
}

void Display_Words(const int & Test_Cases, char **& Words)
{
	for (int i = 0; i < Test_Cases; i++)
	{
		for (int j = 0; Words[i][j]!='\0'; j++)
		{
			cout<<Words[i][j]<<" ";
		}
		cout<<endl;
	}
}

//no need for this
void Display_Word_Search (const int & max, char **Word_Search)
{
	for (int i = 0; i < Grid_Dimensions_X; i++)
	{
		for (int j = 0; j < Grid_Dimensions_Y; j++)
			{
				cout<<Word_Search[i][j]<<" ";
			}
	cout<<endl;
	}
}

//If the Position is Verified, then this function will copy the word in that position
void Copy_Word (int Where, int R, int C, int Len, char ** &Grid, char ** Word)
{
	if (Where == 1) //Left to Right
	{
		int k = 0;
		for (int i = C; i < (Len + C) ; i++)
		{
			Grid[R][i] =  Word[Word_X][k];
			k++;
		}
	}
	else if (Where == 2) //Right to Left
	{
		int k = 0;
		for (int j = C ; j > (C - Len) ; j--)
		{
			Grid[R][j] = Word[Word_X][k];
			k++;
		}
	}
	else if (Where == 3) //Top to Bottom
	{
		int k = 0;
		for (int i = R; i < (Len + R); i++)
		{
			Grid[i][C] = Word[Word_X][k];
			k++;
		}
	}
	else if (Where == 4) //Bottom to Top
	{
		int k = 0;
		for (int i = R; i > (R - Len); i--)
		{
			Grid[i][C] = Word[Word_X][k];
			k++;
		}
	}
	else if (Where == 5) //Diagonal Top Right
	{
		//Rows Decrease and Cols Increase
		int j = C;
		int word_J = 0;
		for (int i = R; i > (R - Len); i--)
		{
			Grid[i][j] = Word[Word_X][word_J];
			j++;
			word_J++;
		}

	}
	else if (Where == 6) //Diagonal Top Left
	{
		//Rows and Cols Both Decrease
		
		int word_I = Word_X;
		int word_J = 0;
		int j = C;
		for (int i = R; i > (R - Len); i--) //CONDTION HERE IS IMPORTANT
		{
				Grid[i][j] = Word[word_I][word_J];
				word_J++;
				j--;
		}
	}
	else if (Where == 7) //Diagonal Bottom Left
	{
		//Rows Increase and Cols Decrease
		int word_I = Word_X;
		int word_J = 0;
		int j = C;
		for (int i = R; i < (R + Len); i++)
		{
				Grid[i][j] = Word[word_I][word_J];
				word_J++;
				j--;
		}
	}
	else if (Where == 8) //DIagonal Bottom Right
	{
		//Rows and COls both Increase
		
		int word_I = Word_X;
		int word_J = 0;
		int j = C;
		for (int i = R; i < (R + Len); i++)
		{
				Grid[i][j] = Word[word_I][word_J];
				word_J++;
				j++;
		}

	}
}

//This Function will generate a random letter to fill in the left over indices on the grid
char Generate_Random_Letter()
{
	char Letter;
    int r;

	r = rand() % 26;					// generate a random number from 0 to 26
	Letter = 'a' + r;					// Convert to a character from a-z (1 to 26)
	if (Letter<=122 && Letter>=97)
		  Letter = Letter - 32;			//We want capital letters only

	return Letter;
}

//The Following  8 Functions are CHECKS to place a word in the desired directions
bool Cells_Empty_Right (const int R, int C, const int len,char ** & Grid)
{
	for (int j = C; j < (len + C); j++)
	{
		if (j >= Grid_Dimensions_Y || j < 0 || Grid[R][j]!='0' )
		{
			return false;
		}
	}
	return true;
}

bool Cells_Empty_Left(int x, int y, int len, char ** Grid)
{
	//Column Decreases and Rows remains constant
	if (y < (y - len))
		return false;

	for (int j = y; j > (y - len) ; j--)
	{
		if (j < 0 || j>=Grid_Dimensions_Y || Grid[x][j]!='0')
		{
			return false;
		}
	}
	return true;
}

bool Cells_Empty_Up(int x, int y, int len, char ** Grid)
{
	if (x<(x-len))
	{
		return false;
	}
	for (int i = x; i > (x - len); i--)
	{
		if (i >= Grid_Dimensions_X || i < 0 || Grid[i][y]!='0')
		{
			return false;
		}
	}
	return true;
}

bool Cells_Empty_Down(int x, int y, int len, char ** Grid)
{
	if (x > (x+len))
		return false;
	for (int r = x; r < (x + len); r++)
	{
		if (r >= Grid_Dimensions_X || r < 0 || Grid[r][y]!='0' )
		{
			return false;
		}
	}
	return true;
}

bool Cells_Empty_Top_Right(int x, int y, int len, char ** Grid)
{
	int j = y;
	//Rows Decrease and Cols Increase

	if (x < (x - len))
		return false;
	for (int i = x; i > (x - len); i--)
	{
		if (j > (y+len))
			return false;
		if ( j < (y + len))
		{
			if (i<0 || i>=Grid_Dimensions_X || j>=Grid_Dimensions_Y || j<0)
				return false;
			else if (i>=0 && i<Grid_Dimensions_X && j >=0 && j<Grid_Dimensions_X)
			{
				if (Grid[i][j]!='0')
				{
					return false;
				}
			}
		}
		else
			return false;
		j++;
	}
	return true;
}

bool Cells_Empty_Bottom_Right(int x, int y, int len, char **Grid)
{
	//Rows Increase and Columns Increase
	int j = y;
	for (int i = x ; i < (len + x) ; i++)
	{
			if (i < 0 ||i >= Grid_Dimensions_X|| j >= Grid_Dimensions_X || j < 0 )
			{
				return false;
			}
			else if (i >=0 && i<Grid_Dimensions_X && j >= 0 && j<=Grid_Dimensions_Y)
			{
				if (Grid[i][j] != '0')
				{
					return false;
				}
			}
			j++;
	}
	return true;
}

bool Cells_Empty_Top_Left(int x, int y, int len, char **Grid) //ALL CHECKS IN PLACE
{
	//Rows decrease and Cols decrease
	int j = y;
	if (x < (x - len))
	{
		return false;
	}

	for (int i = x ; i > (x - len) ; i--) //THE CONDITION HERE IS IMPORTANT
	{
		if ( j < (y-len))
		{
			return false;
		}
		if (j > (y-len))
		{
			if (i < 0 ||i >= Grid_Dimensions_X|| j >= Grid_Dimensions_Y || j < 0 )
				{
					return false;
				}
			else if (i >=0 && i < Grid_Dimensions_X && j >= 0 && j<=Grid_Dimensions_Y)
				{
					if (Grid[i][j] != '0')
					{
						return false;
					}
				}
		}
			j--;
	}
	return true;
}

bool Cells_Empty_Bottom_Left(int x, int y, int len, char **Grid)
{
	//Rows Increase and Columns Decrease
	int j = y;
	for (int i = x ; i < (len + x) ; i++)
	{
			if (i < 0 ||i >= Grid_Dimensions_X|| j >= Grid_Dimensions_Y || j < 0 )
			{
				return false;
			}
			else if (i >=0 && i<Grid_Dimensions_X && j >= 0 && j<=Grid_Dimensions_Y)
			{
				if (Grid[i][j] != '0')
				{
					return false;
				}
			}
			j--;
	}
	return true;
}

//Header Functions for Search Grid
//GLobal Variables that Record A Word's Coordinates upon being found
//They are copied onto the New Output File
int End_Row = 0;
int End_Col = 0;

//this function will load the HARDCODED file containing list of words to be searched
bool Load_Words_File (char *&File, char **&Words, int & Rows, int & Cols, int & Test_Cases)
{
	ifstream FIN (File);
	if (!FIN)
	{	cout<<"\nThis File Does not Exist!";
		return false;
	}
	FIN >> Rows >> Cols >> Test_Cases;
	

	char Temp_Buffer[40]; //Assuming 1 Word is of maximum 40 char in length
	Words = new char * [Test_Cases];
	FIN.getline(Temp_Buffer,40); //discards garbage values
	
	for (int i = 0; i < Test_Cases; i++)
	{
		FIN.getline(Temp_Buffer,40);
		int Len = strlen(Temp_Buffer) + 1;
		Words[i] = new char [Len];
		Words[i] = GetStringFromBuffer(Temp_Buffer); 
	}

	FIN.close();
	return true;
}

//this function will allocate memory from the heap 
void Allocate_Memory (char ** & G_Ptr, int & Rows, int & Cols)
{
	G_Ptr = new char * [Rows]; 
	for (int i = 0; i < Rows; i++)
		G_Ptr[i] = new char [Cols + 1]; //Null wil be Added at the Extra Index
}

//this function will open & close the HARDCODED file containing the Word Search Grid
bool Load_Grid (char *&File, char ** GPtr, int & Rows, int & Cols)
{
	ifstream INFILE(File);

	if (!INFILE)
	{	cout<<"\nThis WORDS File Does not Exist!";
		return false;
	}

	char A = 0;
	int  i = 0, j = 0;
	for (i = 0 ; i < Rows ; i++)
	{
		for (j = 0; j < Cols; j++)
		{
			INFILE >> A;
			GPtr[i][j] = A;
			
		}
		if (j == Cols)
		{
				GPtr[i][j]='\0';
		}
	}

	INFILE.close();
	return true;
}

//this function will display the grid on the console
void Display_Grid(char ** & GPtr, int & Rows, int &Cols)
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; GPtr[i][j]!='\0'; j++)
		{
			cout<<GPtr[i][j]<<" ";
		}
		cout<<endl;
	}
	
	/*for (int i =0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			cout<<GPtr[i][j];
		}
		cout<<endl;
	}*/
}

//this function frees up space from the heap
void DeAllocate_Memory(char **& GPtr, int & Rows, int Cols)
{
	for (int i = 0; i < Rows; i++)
		delete [] GPtr[i];
	delete []GPtr;
}

//the following 8 functions check for the Existence of a word in a particular direction

bool Search_Left_to_Right(char *& Word, char * & Grid, int col, const int& TCOLS)
{	
	int Len = strlen(Word);
	int index = col + 1;
	for (int i = 1; i < Len; i++)
	{
		if (index >=0 && index < TCOLS) 
		{
				if (Word[i] != Grid[index])
				{
					return false;
				}
		}
		else
			return false;
		index++;
	}
	//cout<<"\nMatch Found at LefttoRight"<<endl;
	//cout<<"Word = "<<Word<<endl;
	End_Col = index;
	return true;
}

bool Search_Right_to_Left(char *& Word, char * & Grid, int col, const int & TCOLS)
{	
	int Len = strlen(Word);
	int index = col - 1;
	
	for (int i = 1; i < Len; i++)
	{
		if (index < TCOLS && index >= 0)
		{
			if (Word[i] != Grid[index])
			{
				return false;
			}
			index--;
		}
		else
			return false;
	}
	End_Col = index;
	return true;
}

bool Search_Up_to_Down(char *& Word,char ** & Grid, int R, int C, const int& TRows)
{
	
	int Len = strlen(Word);
	int index = R + 1;

	for (int i = 1 ; i < Len; i++)
	{
		if (index < TRows && index >= 0)
		{
			if (Grid[index][C] != Word[i])
			{
				return false;
			}
		}
		else
			return false;
		index++;
	}
	
	End_Row = index;
	return true;
}

bool Search_Down_to_Up(char *&Word, char **&Grid, int R, int C, const int & TRows)
{
	int Len = strlen(Word);
	int index = R - 1;

	for (int i = 1; i < Len; i++)
	{
		if (index < TRows && index >=0)
		{
			if (Word[i]!=Grid[index][C])
			{
			return false;
			}
		}
		else
			return false;
		index--;
	}
	End_Row = index;
	return true;
}

bool Search_Diagonal_Up_Right(char *&Word, char **&Grid, int R, int C, const int &TRows, const int &TCols)
{
	int Len = strlen(Word);
	int r_index = R - 1;
	int c_index = C + 1;
	if (r_index < 0 || r_index > TRows || c_index < 0 || c_index > TCols)
	{
		return false;
	}

	for (int i = 1; i < Len; i++)
	{
		if (r_index >= 0 && r_index < TRows)
			{
				if (c_index >= 0 && c_index < TCols)
				{
					if (Grid[r_index][c_index]!=Word[i])
					{
						//cout<<"\nGrid["<<r_index<<"["<<c_index<<"]"<<Grid[r_index][c_index];
						//cout<<"!=Word["<<i<<"]"<<Word[i]<<endl;
						return false;
					}
				}
				else
					return false;
			}
		else
			return false;
		c_index++;
		r_index--;
	}
	End_Row = r_index;
	End_Col = c_index;
	return true;
}

bool Search_Diagonal_Down_Right(char *&Word, char **&Grid, int R, int C, const int &TRows, const int &TCols)
{
	int Len = strlen(Word);
	int r_index = R + 1;
	int c_index = C + 1;
	if (r_index < 0 || r_index > TRows || c_index < 0 || c_index > TCols)
	{
		return false;
	}
	for (int i = 1; i < Len; i++)
	{
		if (r_index >= 0 && r_index < TRows)
			{
				if (c_index >= 0 && c_index < TCols)
				{
					if (Grid[r_index][c_index]!=Word[i])
					{
						return false;
					}
				}
				else
					return false;
			}
		else
			return false;
		c_index++;
		r_index++;
	}
	End_Row = r_index;
	End_Col = c_index;
	return true;

}

bool Search_Diagonal_Down_Left(char *&Word, char **&Grid, int R, int C, const int &TRows, const int &TCols)
{
	int Len = strlen(Word);
	int r_index = R + 1;
	int c_index = C - 1;
	if (r_index < 0 || r_index >= TRows || c_index < 0 || c_index >= TCols)
	{
		return false;
	}
	
	for (int i = 1; i < Len; i++)
	{
		if (r_index >= 0 && r_index < TRows)
			{
				if (c_index >= 0 && c_index < TCols)
				{
					if (Grid[r_index][c_index]!=Word[i])
					{
						
						return false;
					}
				}
				else
					return false;
			}
		else
			return false;
		c_index--;
		r_index++;
	}
	End_Row = r_index;
	End_Col = c_index;
	return true;
}

bool Search_Diagonal_Up_Left(char *&Word, char **&Grid, int R, int C, const int &TRows, const int &TCols)
{
	int Len = strlen(Word);
	int r_index = R - 1;
	int c_index = C - 1;
	if (r_index < 0 || r_index > TRows || c_index < 0 || c_index > TCols)
	{
		return false;
	}
	
	for (int i = 1; i < Len; i++)
	{
		if (r_index >= 0 && r_index < TRows)
			{
				if (c_index >= 0 && c_index < TCols)
				{
					if (Grid[r_index][c_index]!=Word[i])
					{	
					return false;
					}
				}
				else
					return false;
			}
		else
			return false;
		c_index--;
		r_index--;
	}
	End_Row = r_index;
	End_Col = c_index;
	return true;
}
