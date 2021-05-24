#include "20L-1080_Header_Assignment5.h"
//Verify if .txt not added in output file then add

#include <cstring>
#include <string>

//Displays 3 options to Create,Search,Quit
void Menu()
{
	cout << "\n\n\t\t________________________________________________HOME SCREEN___________________________________________.";
	cout<<"\n\n\t\t\tChoose An Option from our Menu Below: \n";
	cout <<"\n\t\tPRESS C if you want to CREATE GRID,";
	cout <<"\n\t\tPRESS S if you want to SEARCH WORDS FROM AN EXISTING GRID, or:";
	cout <<"\n\t\tPRESS Q if you want to EXIT GRIDDY\n\n\n";
	cout << "\n\t\tYour Choice = ";
//	cout << "---------------------------------------------------------------------";
}


//DriverFunction for Creating Grid
void Make_Grid(char **&Words_Ptr, char *WordsFile, char *OutPutFile, int& Rows, int& Cols, int& Test_Cases)
{
	
	//Make a Grid with its Dimensions being the Length of the longest word
	int max = strlen(Words_Ptr[Test_Cases - 1]);

	//UPDATE GLOBAL VARIABLE
	Grid_Dimensions_X = Rows; 
	Grid_Dimensions_Y = Cols;

	//Create a New Word Search of MAX X MAX order
	char ** Word_Search = new char * [Rows];
	for (int i = 0; i < Rows; i++)
		Word_Search[i] = new char [Cols];
	
	//Initialise all the indices in the WordSearch to 0 first
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Cols; j++)
			Word_Search[i][j] = '0';

	//Generate an Array to keep track of when a word is placed
	bool * Word_Placed = new bool [Test_Cases];
	for (int i = 0; i < Test_Cases; i++)
		Word_Placed[i] = false;

	//Place the Largest Words First
	//FIND THE LARGEST WORDS (Length>MAX/2) 
	int * Length_Arr = new int [Test_Cases];
	for (int i = 0; i < Test_Cases; i++)
		Length_Arr[i] = strlen(Words_Ptr[i]);

	//Another Array to keep track of Which Words need to be placed first
	bool * Place_First = new bool [Test_Cases];
	for (int i = 0; i < Test_Cases; i++)
		Place_First[i] = false;
	for (int i = 0; i < Test_Cases; i++)
	{
		if (Length_Arr[i] > max/2 + 1)
			Place_First[i] = true;
	}

	//NOW PLACE Large WORDS IN THE GRID
	int p = Test_Cases - 1;
	bool one_diagonal = false;
	while (p >= 0)
	{
		if (Place_First[p] == true)
			for (int i = Rows - 1 ; i >= 0 ; i--)
		{
			for (int j = Cols -1; j >=0 ; j--)
			{
				if (Word_Placed[p] == false)
				{
					if (one_diagonal == false)
					{
						if ( Cells_Empty_Top_Left(i,j,Length_Arr[p],Word_Search) == true)
						{
							one_diagonal = true;
							Word_X = p;
							Copy_Word(6,i,j,Length_Arr[p],Word_Search,Words_Ptr);
							Word_Placed[p] = true;
							break;
						}
					}
					else 
					{	
						if (Cells_Empty_Up(i,j,Length_Arr[p],Word_Search) == true)
						{
							Word_X = p;
							Copy_Word(4,i,j,Length_Arr[p],Word_Search,Words_Ptr);
							Word_Placed[p] = true;
							break;
						}
						else if (Cells_Empty_Left(i,j,Length_Arr[p],Word_Search) == true)
						{
							Word_X = p;
							Copy_Word(2,i,j,Length_Arr[p],Word_Search,Words_Ptr);
							Word_Placed[p] = true;
							break;
						}
						
					}
				}
			}
		}
		p--;
	}

	
	

	//START LOOP FOR THE REST OF THE WORDS THEN (automatically adjusted)

	bool once_vertical = false; //at least once a word is placed vertically
	int k = 0; //iterator of Test_Cases
	while (k < Test_Cases)
	{
		for (int i = 0; i < Rows; i++) //TESTING FOR NOW
		{
			for (int j = 0; j < Cols; j++)
			{
				if (Word_Placed[k] == false)
				{
					if (Word_Search[i][j] == '0') //Must Not be Occupied
					{
						int Len = strlen(Words_Ptr[k]);

						//Length Check and Empty Cell Check in different directions
						if (k == 0) //Smallest Word at the Top in the sorted List
						{
							//assuming a sorted list, smallest word at the top
							if (Cells_Empty_Down(i,j,Len,Word_Search)==true)
							{
								once_vertical = true;
								Word_X = k;
								Copy_Word(3,i,j,Len,Word_Search,Words_Ptr);
								Word_Placed[k] = true;
								break;
							}
						}


						if (Cells_Empty_Right(i,j,Len,Word_Search) == true)
						{
							Word_X = k;
							Copy_Word(1,i,j,Len,Word_Search,Words_Ptr);
							Word_Placed[k] = true;
							break;
						}	
						else if (Cells_Empty_Bottom_Right(i,j,Len,Word_Search) == true)
						{
							Word_X = k;
							Copy_Word(8,i,j,Len,Word_Search,Words_Ptr);
							Word_Placed[k] = true;
							break;
						}
						else if (Cells_Empty_Bottom_Left(i,j,Len,Word_Search) == true)
						{
							Word_X = k;
							Copy_Word(7,i,j,Len,Word_Search,Words_Ptr);
							Word_Placed[k] = true;
							break;
						}
						else if (Cells_Empty_Down(i,j,Len,Word_Search) == true)
						{
							Word_X = k;
							Copy_Word(3,i,j,Len,Word_Search,Words_Ptr);
							Word_Placed[k] = true;
							cout<<endl;
							break;
						}
						else if (Cells_Empty_Top_Right(i,j,Len,Word_Search) == true)
						{
							Word_X = k;
							Copy_Word(5,i,j,Len,Word_Search,Words_Ptr);
							Word_Placed[k] = true;
							cout<<endl;
							break;
						}
						else if (Cells_Empty_Top_Left(i,j,Len,Word_Search) == true)
						{
							Word_X = k;
							Copy_Word(6,i,j,Len,Word_Search,Words_Ptr);
							Word_Placed[k] = true;
							cout<<endl;
							break;
						}
					}
				}
			}
		}
	k++;
}



		//Now, for all the words that aren't placed 
		cout<<"\nProcessing . . . \n";
		cout<<"\nProcessing . . . \n\n\n";
		


		//FILL ALL 0S WITH RANDOM CHARACTERS	
		//cout<<"\nGRID: \n";

		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				if (Word_Search[i][j] == '0')
					Word_Search[i][j] = Generate_Random_Letter();
			}
			
		}
		
		//cout << "\nGrid: "<<endl;
		//Display_Word_Search(Rows,Word_Search);

		//Fill the Grid with Letters
		ofstream OutFile (OutPutFile);
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				OutFile<<Word_Search[i][j]<<" ";
			}
			OutFile<<endl;
		}

		OutFile.close();
		cout<<"\n\n\t\t\t\t This Grid has been SAVED as " << OutPutFile << "\n\n\n\t";

		//Memory De-Allocation
		DeAllocate_Memory(Words_Ptr,Test_Cases);
		DeAllocate_Memory(Word_Search,Rows);
		
		delete [] Word_Placed;
		delete [] Length_Arr;
		delete [] Place_First;

}


//DriverFunction for Searching through a Grid
void Search_Grid (char *GridFile, char *WordFile, char *OutputFile)
{
	
	//Load File Containing Words
	int Rows = 0, Cols = 0, Test_Cases = 0;
	char ** Words = 0;
	Load_Words_File(WordFile,Words,Rows,Cols,Test_Cases);
	
	//cout << "\nWords Read: \n";
	//Display_Words(Test_Cases,Words);	

	//Load File Containing Grid
	char ** Grid = 0;
	Allocate_Memory(Grid,Rows,Cols);
	Load_Grid(GridFile,Grid,Rows,Cols);
		
	//cout << "\nGrid Read: \n";
	//Display_Grid(Grid,Rows,Cols);
	
	//Create an Array to keep track of If a Word has been located in the Word Search
	bool * Found_Record = new bool [Test_Cases];
	for (int i = 0; i < Test_Cases; i++)
		Found_Record[i] = false;

	//Create an Output File to Place Coordinates of every Found Word in the WordSearch
	ofstream New_File(OutputFile);
	
	//Find How many times in the Entire Word Search the initial letter of each word occurs
	//This will later be compared against a variable called "times_word" to 
	//see if all possible ways have been tried to locate a word

	int * Initial_Letterrs_Record = new int [Test_Cases];
	for (int i = 0; i < Test_Cases; i++)
		Initial_Letterrs_Record[i] = 0;

	for (int i = 0; i < Test_Cases; i++)
	{
		for (int row = 0; row < Rows; row++)
		{
			for (int col = 0; col < Cols; col++)
			{
				if (Words[i][0] == Grid[row][col])
					Initial_Letterrs_Record[i]++;
			}
		}
	}
	

	//Now Use the initial letters of every word and Find the Word in all directions

	bool FOUND_ONCE = false;
	int k = 0; //Iterator for Test Cases

	cout << "\n\t\t\tCoordinates: "<<endl;
	while (k < Test_Cases)
	{		
		char initial_Letter = Words[k][0]; 
		int times_word = 0;
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0 ; j < Cols ; j++)
			{
				if (Grid[i][j] == initial_Letter) 
				{
					times_word++; //Keeps a track of if all possible combinations from every point of initial letters

					FOUND_ONCE = false;
					
					while (FOUND_ONCE != true)
					{
						if (Search_Left_to_Right(Words[k],Grid[i],j,Cols) == true)
						{
							FOUND_ONCE = true;
							Found_Record[k] = true;
							New_File<<"{"<<i<<","<<j<<"}"<<"{"<<i<<","<<End_Col - 1 <<"}"<<endl;														
							cout<<"\t\t\t{"<<i<<","<<j<<"}"<<"{"<<i<<","<<End_Col - 1 <<"}"<<endl;

							break;
						}
						
						else if (Search_Right_to_Left(Words[k],Grid[i],j,Cols) == true)
						{
							FOUND_ONCE = true;
							Found_Record[k] = true;
							New_File<<"{"<<i<<","<<j<<"}"<<"{"<<i<<","<<End_Col + 1 <<"}"<<endl;
							cout<<"\t\t\t{"<<i<<","<<j<<"}"<<"{"<<i<<","<<End_Col + 1 <<"}"<<endl;
							break;
							
						}
						else if (Search_Up_to_Down(Words[k],Grid,i,j, Rows) == true)
						{
							FOUND_ONCE = true;
							Found_Record[k] = true;
							New_File<<"{"<<i<<","<<j<<"}"<<"{"<<End_Row - 1<<","<<j<<"}"<<endl;
							cout<<"\t\t\t{"<<i<<","<<j<<"}"<<"{"<<i<<","<<End_Row - 1 <<"}"<<endl;
							break;
						}
						else if (Search_Down_to_Up(Words[k],Grid,i,j,Rows) == true)
							{
								FOUND_ONCE = true;
								Found_Record[k] = true;
								New_File<<"{"<<i<<","<<j<<"}"<<"{"<<End_Row + 1<<","<<j<<"}"<<endl;
								cout<<"\t\t\t{"<<i<<","<<j<<"}"<<"{"<<i<<","<<End_Row + 1 <<"}"<<endl;
								break;
							}
					
						else if (Search_Diagonal_Down_Left(Words[k],Grid,i,j,Rows,Cols) == true)
						{
							FOUND_ONCE = true;
							Found_Record[k] = true;
							New_File<<"{"<<i<<","<<j<<"}"<<"{"<<End_Row - 1<<","<<End_Col + 1 <<"}"<<endl;
							cout<<"{"<<i<<","<<j<<"}"<<"{"<<End_Row - 1<<","<<End_Col + 1 <<"}"<<endl;
							break;
						}
						else if (Search_Diagonal_Down_Right(Words[k],Grid,i,j,Rows,Cols) == true)
							{
								FOUND_ONCE = true;
								Found_Record[k] = true;
								New_File<<"{"<<i<<","<<j<<"}"<<"{"<<End_Row - 1<<","<<End_Col - 1 <<"}"<<endl;
								cout<<"{"<<i<<","<<j<<"}"<<"{"<<End_Row - 1<<","<<End_Col - 1 <<"}"<<endl;
								break;
							}
						else if (Search_Diagonal_Up_Left(Words[k],Grid,i,j,Rows,Cols) == true)
						{
							FOUND_ONCE = true;
							Found_Record[k] = true;
							New_File<<"{"<<i<<","<<j<<"}"<<"{"<<End_Row + 1<<","<<End_Col + 1 <<"}"<<endl;
							cout <<"{"<<i<<","<<j<<"}"<<"{"<<End_Row + 1<<","<<End_Col + 1 <<"}"<<endl;
							break;
						}
						else if (Search_Diagonal_Up_Right(Words[k],Grid,i,j,Rows,Cols) == true)
							{
								FOUND_ONCE = true;
								Found_Record[k] = true;
								New_File<<"{"<<i<<","<<j<<"}"<<"{"<<End_Row + 1<<","<<End_Col - 1 <<"}"<<endl;
								cout <<"{"<<i<<","<<j<<"}"<<"{"<<End_Row + 1<<","<<End_Col - 1 <<"}"<<endl;
								break;
							}
						else
							{
								FOUND_ONCE = true;
								if (Found_Record[k] == false && times_word==Initial_Letterrs_Record[k])
								{
									New_File<<"Not Found\n";
									cout << "\t\t\tNot Found\n";
								}
						}
					}
				}
			}
		}
		
		k++;
}

	//DEALLOCATION OF SPACE ON HEAP
	DeAllocate_Memory(Grid,Rows,Cols);
	DeAllocate_Memory(Words,Test_Cases,Cols);
	delete [] Found_Record;
	delete [] Initial_Letterrs_Record;

	New_File.close();
	cout<<endl;
}


//Wrapper Function 
int main()
{
	cout << "\n\n\t\t---------------------------------------------WELCOME TO GRIDDY!---------------------------------------\n";
	
	Menu();
	char UserChoice = 0;
	
	bool EndProgram = false;
	
	while (EndProgram == false)
		{
			cin >> UserChoice;

			while (UserChoice!='C' && UserChoice!='S' && UserChoice!='Q')
			{
				cout << "\n\t\tKindly Choose from the Above 3 Letters only...\n";
				cout << "\t\tEnter Choice Again: ";
				cin >> UserChoice;
			}

			cout << "\n\n\t\t " << UserChoice << " is a Valid Choice. \n";
			
			if (UserChoice == 'C')
			{
				cout << "\n\t\tEnter the Name of the Input Txt File holding Words: ";
				char InputFile[15];
				cin >> InputFile;
				
				char *Ptr = strstr(InputFile,".txt");

				//Verify that .txt Extension is Present
				while (!Ptr)
				{
					cout << "\n\t\tOnly .txt File is Supported. Enter Again: ";
					cin >> InputFile;
					Ptr = strstr(InputFile,".txt");
				}

				cout << "\n\t\tFile Format Supported of " << InputFile;
				ifstream FIN (InputFile);
				
				if (!FIN)
				{
					cout << "\n\t\t\tThis txt file does NOT exist. Enter a valid file name: ";
					cin >> InputFile;
				}
				FIN.close();

				int Words = 0;
				cout << "\n\t\tEnter the Number of Words in this File: ";
				cin >> Words;

				int Rows = 0, Cols = 0;
				cout << "\n\t\tEnter the Number of Rows you want in the Grid.: ";
				cin >> Rows;
				cout << "\n\t\tEnter the Number of Cols you want in the Grid.: ";
				cin >> Cols;
		
				//Open File and Read Words & Sort them in Ascending Order
			
				char **Words_Ptr = 0;
				ifstream Fin(InputFile);
				Allocate_Memory(Fin,Words_Ptr,Words);
				Fin.close();
				Sort_List(Words_Ptr,Words);

				//Verify if User-Requested Dimensions are possible
				int Length_OfLongestWord = strlen(Words_Ptr[Words-1]);
				if (Rows < Length_OfLongestWord || Cols < Length_OfLongestWord)
				{
					cout << "length of longest word = "<<Length_OfLongestWord<<endl;
					cout << "\n\t\t\tGrid CANNOT be formed with these dimensions, Press Any Key to return to the home screen::: ";
					char AnyKey = 0;
					cin >> AnyKey; //Return HomeScreen
					Menu();
				}
				else
				{
					cout << "\n\t\tRows & Cols are appropriate. \n";
					cout << "\n\t\tEnter the Name of the OutPut Txt File to Save the Grid:";
					
					char OutputFile[15];
					cin >> OutputFile;
					char *Ptr  = strstr(OutputFile,".txt");
					while (!Ptr)
					{
						cout << "\n\t\tOnly a .txt File is supported. Enter again: ";
						cin >> OutputFile;
						Ptr  = strstr(OutputFile,".txt");
					}

					//Call the Function to generate OutPut File 
					Make_Grid(Words_Ptr, InputFile,OutputFile,Rows,Cols,Words);
				
					cout << "\n\t\tGrid Saved Successfully in "<< OutputFile << "\n";
					cout << "\nPress any key to return to Home Screen::: \n";
					char AnyKey = 0;
					cin >> AnyKey; //Return to HomeScreen
					Menu();
				}
			}
			else if (UserChoice == 'S')
			{
				cout << "\n\t\tEnter the Input TXT File Holding the GRID: ";
				char GridFile[15];
				cin >> GridFile;
				ifstream fIN (GridFile);
				while (!fIN)
				{
					cout << "\n\t\t "<< GridFile <<" Does NOT Exist. Enter a Valid File Name: ";
					cin >> GridFile;
				}
				fIN.close();


				cout << "\n\t\tEnter the Input TXT File Holding WORDS to be searched: ";
				char WordFile[15];
				cin >> WordFile;

				ifstream FIN (WordFile);
				while (!FIN)
				{
					cout << "\n\t\t "<< WordFile <<" Does NOT Exist. Enter a Valid File Name: ";
					cin >> WordFile;
				}
				FIN.close();

				//Verify both these files end in .txt extension

				cout << "\n\t\tEnter the Name of the OUTPUT File you want to place Search Results in: ";
				char OutputFile[15];
				cin >> OutputFile;
				char *Ptr = strstr(OutputFile,".txt");
				while (!Ptr)
				{
					cout<< "\n\t\tOnly a .txt File Format is supported.\n";
					cin >> OutputFile;
					Ptr = strstr(OutputFile,".txt");
				}

				cout << "\n\t\tCoordinates of Words Found: \n";
				Search_Grid(GridFile,WordFile,OutputFile);
				cout << "\nSEARCH SUCCESSFUL! \n";
				cout << "\n\n\t\t\tThese Coordinates will be saved in "<<OutputFile<<"!"<<endl;
				cout << "\n\t\tPress Any Key to Continue to HomeScreen::: ";
				char AnyKey = 0;
				cin >> AnyKey;
				Menu();
			}
			else if (UserChoice == 'Q')
				EndProgram = true;
		}
	

	cout << "\n------------------------------------THANK YOU FOR USING GRIDDY!------------------------------------\n\n\n";
	return 0;
}




