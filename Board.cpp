#include <iostream>
#include "Board.hpp"
#include <iomanip>
#include <vector>
using namespace std;

Board::Board():Board(3,3)
{
  numRows = 3;
  numCols = 3;
  panel = new int*[3];
  for(int i = 0; i < 3; i++)
  {
    panel [i] = new int[3];
    for(int j =0; j < 3; j++)
    {
      panel[i][j] = 0;
    }
  }
  target = 32;
  max = 0;
}

Board::Board(int m)
{
 if(m>=1)
  {
    numRows = m;
    numCols = m;
  }
  else 
  {
    numRows = 3;
    numCols = 3;
  }
  panel = new int*[numRows];
  for(int i = 0; i < numRows; i++)
  {
    panel [i] = new int[numCols];
    for(int j =0; j < numCols; j++)
    {
      panel[i][j] = 0;
    }
  }
  target = 32;
  max = 0;
}
Board::Board(int m,int n)
{
  if(m>=1 && n>=1)
  {
    numRows = m;
    numCols = n;
  }
  else 
  {
    numRows = 3;
    numCols = 3;
  }
  

  panel = new int*[numRows];
  for(int i = 0; i < numRows; i++)
  {
    panel [i] = new int[numCols];
    for(int j =0; j < numCols; j++)
    {
      panel[i][j] = 0;
    }
  }
  target = 32;
  max = 0;
  
}
Board::~Board()
{
  for(int i = 0; i <numRows;i++)
  {
    delete[] panel[i];
    panel[i] = nullptr;    
  }
  delete[] panel;
  panel = nullptr;

}

void printSeparateLine(int numCols)
{
  cout << "+";
  for(int i = 0; i < numCols; i++)
  {
    cout << "----+";   
  }
  cout << endl;
}

void Board::print() const
{
  printSeparateLine(numCols);
  for(int i = 0; i < numRows; i++)
  {
    cout << "|";
    for(int j = 0; j < numCols; j++)
    {
      if(panel[i][j] > 0)
      {
        cout << setw(4) << panel[i][j] << "|";
      }
      else
      {
        cout << setw(4) << " " <<  "|";    
      }
    }
    cout << endl;
    printSeparateLine(numCols);

  }
}



void Board::selectRandomCell(int& row, int& col)
{
  int numZeros = 0;
  for(int i = 0; i < numRows; i++)
  {
    for(int j = 0; j < numCols; j++)
    {
      if(panel[i][j] == 0)
      {
        numZeros++;
      }
    }
  }

  if(numZeros == 0)
  {
    cout << "Game over. Try again." << endl;
    exit(0); 
  }
  //else return;
 
  else
  {
    /*if(noAdjacentSameValue() && numZeros == 1)
    {
    
    
      for(int i = 0; i < numRows; i++)
      {
        for(int j = 0; j < numCols; j++)
        {
          if(panel[i][j] == 0)
          {
            panel[i][j] = 1;    
          }
        }
      
      print();
      cout << "Game over. Try again." << endl;
      exit(0);
      }
        
    }*/
    
    if(numZeros == 1)
    {
      for(int i = 0; i < numRows; i++)
      {
        for(int j = 0; j < numCols; j++)
        {
          if(panel[i][j] == 0)
          {
            panel[i][j] = 1;    
          }
        }
      }
      print();
    

    if(noAdjacentSameValue())
    {
      cout << "Game over. Try again." << endl;
      exit(0);
      }
    
    }
    

    else if(numZeros > 1)
    {
      struct Coor
      {
        int row;
        int col;
      };
      vector<Coor> emptyCells;
      Coor cell;
      for(int i = 0; i <numRows; i++)
      {
        for(int j = 0; j < numCols; j++)
        {
          if(panel[i][j] == 0)
          {
            cell.row =  i;
            cell.col = j;
            emptyCells.push_back(cell);
          }    
        }
      }
      int size = emptyCells.size();
      int index = rand() % size;
        
      
  /* if(size == 0 && noAdjacentSameValue())
  {
    cout << "Game over. Try again." << endl;
    exit(0); 
  } */

      int r = index/numCols;
      int c = index%numCols;
      panel[r][c] = 1;
      //panel[2][0] = 1;
      print();
    }
  }
}



bool Board::noAdjacentSameValue() const
{
  int numZero = 0;
  for(int i = 0; i < numRows; i++)
  {
    for(int j = 0; j < numCols; j++)
    {
      if(panel[i][j] == 0)
      {
        numZero++;
      }
    }
  }


  if(numZero >= 1)
    return false;
  
    
  for(int i = 0; i < numRows; i++)
  {
    for(int j = 0; j < (numCols-1); j++)
    {
      if(panel[i][j] == panel[i][j+1])
        return false;
      
    }
  }

  for(int j = 0; j < numCols; j++)
  {
    for(int i = 0; i < (numRows-1); i++)
    {
      if(panel[i][j] == panel[i+1][j])
        return false;
    }
  }

  return true;
}

/*Board::~Board()
{
  for(int i = 0; i <numRows;i++)
  {
    delete[] panel[i];
    panel[i] = nullptr;    
  }
  delete[] panel;
  panel = nullptr;

}*/

/*void printSeparateLine(int numCols)
{
  cout << "+";
  for(int i = 0; i < numCols; i++)
  {
    cout << "----+";   
  }
  cout << endl;
}*/

/*void Board::print() const
{
  printSeparateLine(numCols);
  for(int i = 0; i < numRows; i++)
  {
    cout << "|";
    for(int j = 0; j < numCols; j++)
    {
      if(panel[i][j] > 0)
      {
        cout << setw(4) << panel[i][j] << "|";
      }
      else
      {
        cout << setw(4) << " " <<  "|";    
      }
    }
    cout << endl;
    printSeparateLine(numCols);

  }
}*/

void Board::pressDown()
{
  int* temp = new int[numRows];
  int toWrite;
  for(int j = 0; j < numCols; j++)
  {
    for(int k = 0; k < numRows; k++)
    {
      temp[k] = 0;
    }
    toWrite = numRows -1;
    for(int i = numRows -1; i >= 0; i--)
    {
      if(panel[i][j] > 0)
      {
        temp[toWrite] = panel[i][j];
        toWrite--;
      }
    }
    for(int k = numRows -1; k > 0; k--)
    {
      if(temp[k] == temp[k-1])
      {
        temp[k] *= 2;
        if (max < temp[k])
        {
          max = temp[k];
        }

        temp[k-1] = 0;
        k--; 
      }
    }
    int i = numRows -1;
    int k = numRows -1;
    while(k >=0)
    {
      if(temp[k] > 0)
      {
        panel[i][j] = temp[k];
        i--;
      }
      k--;
    }
    while(i >= 0)
    {
      panel[i][j] = 0;
      i--;
    }
    
  }
 
  
  int row = -1;
  int col = -1;
  selectRandomCell(row, col);
  //print();  
  delete[] temp;
  temp = nullptr;
 
}

void Board::pressUp()
{
  int* temp = new int[numRows];
  int toWrite;
  for(int j = 0; j < numCols; j++)
  {
    for(int k = 0; k < numRows; k++)
    {
      temp[k] = 0;
    }
    toWrite = 0;
    for(int i = 0; i < numRows; i++)
    {
      if(panel[i][j] > 0)
      {
        temp[toWrite] = panel[i][j];
        toWrite++;
      }
    }
    
    for(int k = 0; k < numRows; k++)
    {
      if(temp[k] == temp[k+1])
      {
        temp[k] *= 2;
        if (max < temp[k])
        {
          max = temp[k];
        }
        temp[k+1] = 0;
        k++;
      }
    }
    
    int i = 0;
    int k = 0;
    while(k < numRows)
    {
      if(temp[k] > 0)
      {
        panel[i][j] = temp[k];
        i++;
      }
      k++;
    }
    while(i < numRows)
    {
      panel[i][j] = 0;
      i++;
    }
  
  }
  int row = -1; 
  int col = -1;
  selectRandomCell(row, col); 
  //print();

  delete[] temp;
  temp = nullptr;
}


void Board::pressLeft()
{
  int* temp = new int[numCols];
  int toWrite;
  for(int i = 0; i < numRows; i++)
  {
    for(int k = 0; k < numCols; k++)
    {
      temp[k] = 0;
    }
    toWrite = 0;
    for(int j = 0; j < numCols; j++)
    {
      if(panel[i][j] > 0)
      {
        temp[toWrite] = panel[i][j];
        toWrite++;
      }
    }
        
    for(int k = 0; k < numCols; k++)
    {
      if(temp[k] == temp[k+1])
      {
        temp[k] *= 2;
        if (max < temp[k])
        {
          max = temp[k];
        }
        temp[k+1] = 0;
        k++;
      }
    }

    int j = 0;
    int k = 0;
    while(k < numCols)
    {
      if(temp[k] > 0)
      {
        panel[i][j] = temp[k];
        j++;
      }
      k++;
    }
    while(j < numCols)
    {
      panel[i][j] = 0;
      j++;
    }  
  }

  int row = -1;
  int col = -1;
  selectRandomCell(row, col); 
  //print();
  delete[] temp;
  temp = nullptr;
}
void Board::pressRight()
{
  int* temp = new int[numCols];
  int toWrite;
  for(int i = 0; i < numRows; i++)
  {
	  for(int j = numCols - 1; j >= 0; j--)
	  {
		  temp[j] = 0;	
	  }
	  toWrite = numCols -1;
	  for(int j = numCols -1; j >= 0; j--)
	  {
		if(panel[i][j] > 0)
		{
			temp[toWrite] = panel[i][j];
			toWrite--;
		}	
	}
	for(int j = numCols -1; j >= 1; j--)
	{
		if(temp[j] == temp[j-1])
		{
			temp[j] *= 2;
			temp[j-1] = 0;	
			if(max < temp[j])
			{
				max = temp[j];
			}
			j--;	
		}	
	}
	toWrite = numCols -1;
	for(int j = numCols -1; j >= 0; j--)
	{
		if(temp[j] > 0)
		{
			panel[i][toWrite] = temp[j];
			toWrite--; 
		}
	}
	while(toWrite >= 0)
	{
		panel[i][toWrite] = 0;
		toWrite--;
	}	
}

delete[] temp;
temp = nullptr;
int row = -1;
int col = -1;
selectRandomCell(row, col);
}


void Board::start()
{
  int round = 1;
  int row = 3;
  int col = 3;
  selectRandomCell(row, col);
  //selectRandomCell(row, col);
  while (true)
  {
    if (max == target)
    {
      cout << "Congratulation!";
      break;
    } 
        //reference: https://stackoverflow.com/questions/10463201/getch-and-arrow-codes            
    if (getchar() == '\033') 
    { // if the first value is esc
      getchar(); // skip the [
      switch(getchar()) 
      { // the real value
        case 'A':
          // code for arrow up
          cout << "Round " << setw(4) << round << ": ";
          cout << "Press UP. " << endl;
          pressUp();
          round++;
          break;
        case 'B':
        // code for arrow down
          cout << "Round " << setw(4) << round << ": ";
          cout << "Press DOWN. " << endl;
          pressDown();
          round++;
          break;
        case 'C':
          // code for arrow right
          cout << "Round " << setw(4) << round << ": ";
          cout << "Press RIGHT. " << endl;
          pressRight();
          round++;
          break;
        case 'D':
        // code for arrow left
          cout << "Round " << setw(4) << round << ": ";
          cout << "Press LEFT. " << endl;
          pressLeft();
          round++;
          break;
              //You finish the rest code
        } //end of switch
      } //end of if
  } //end of while
 }