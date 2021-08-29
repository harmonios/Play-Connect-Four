
// Name: Kashif Moattar

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

const int max = 1024;
const int wrong = -1;
const int tie = 1;

// max(int num1, int num2) compares two numbers, and then return the higher
// value
int max(int num1, int num2) {
  if (num1 > num2) {
    return num1;
  } else {
    return num2;
  }
}

// horizontal(Current_Player, width, height, length, board) checks within
// an array board if the Current_Player reaches length value when it
// is seen length times in a row horizontal, outputting a bool of true
// or false
bool horizontal(int Current_Player, int width, int height,
                int length, int board[]) {
  const int Board_Length = width * height;
  int count_horizontal = 0;
  int count_width = 0;
  int Current_Comparer_h = 0;
  if (Current_Player == 1) {
    Current_Comparer_h = Current_Player;
  }
  if (Current_Player == 2) {
    Current_Comparer_h = Current_Player;
  }

  for (int i = 0; i < Board_Length; i++) {
    if (count_horizontal >= width) {
      count_horizontal = 0;
      count_width = 0;
    }
    if (count_horizontal < width) {
      if (board[i] == Current_Comparer_h) {
        count_horizontal++;
        count_width++;
      } else {
        count_horizontal++;
        count_width = 0;
      }
    }
    if (count_width >= length) {
      return true;
    }
  }
  return false;
}

// vertical(Current_Player, width, height, length, board) checks within
// an array board if the Current_Player reaches length value when it
// is seen length times in a row vertically, outputting a bool of true
// or false
bool vertical(int Current_Player, int width, int height,
              int length, int board[]) {
  int count_vertical = 0;
  int count_height = 0;
  int Current_Comparer_v = 0;
  if (Current_Player == 1) {
    Current_Comparer_v = Current_Player;
  }
  if (Current_Player == 2) {
    Current_Comparer_v = Current_Player;
  }
  int position = 0;
  for (int i = 0; i < width; i++) {
    position = i;
    while (count_vertical < height) {
      if (board[position] == Current_Comparer_v) {
        count_height++;
      }
      if (board[position] != Current_Comparer_v) {
        count_height = 0;
      }
      count_vertical++;
      position = position + width;
      if (count_height >= length) {
        return true;
      }
    }
    count_vertical = 0;
    count_height = 0;
  }
  return false;
}

// diagonal_right(Current_Player, width, height, length, board) checks
// within an array board if the Current_Player reaches length value when it
// is seen length times in a row diagonally to the right, 
// outputting a bool of true or false
bool diagonal_right(int Current_Player, int width, int height,
                    int length, int board[]) {
  const int Board_Length = width * height;
  bool is_Win = false;
  int win_Count = 0;
  int Current_Comparer_d = 0;
  int current_width = 0;
  if (Current_Player == 1) {
    Current_Comparer_d = Current_Player;
  }
  if (Current_Player == 2) {
    Current_Comparer_d = Current_Player;
  }
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if(board[j + (i * width)] == Current_Comparer_d) {
        win_Count++;
        current_width = j;
        for (int k = j + 1 + width + (i * width); 
             current_width < width - 1 &&
             k < Board_Length; k = width + k + 1) {
          if (board[k] == Current_Comparer_d) {
            win_Count++;
            if (win_Count >= length) {
              is_Win = true;
              return true;
            } 
          } else {
            win_Count = 0;
          }
          current_width++;
        }
        win_Count = 0;
      }
    }
  }
  return false;
}

// diagonal_left(Current_Player, width, height, length, board) checks
// within an array board if the Current_Player reaches length value when it
// is seen length times in a row diagonally to the left, 
// outputting a bool of true or false
bool diagonal_left(int Current_Player, int width, int height,
                   int length, int board[]) {
  const int Board_Length = width * height;
  bool is_Win = false;
  int win_Count = 0;
  int Current_Comparer_d = 0;
  int current_width = 0;
  if (Current_Player == 1) {
    Current_Comparer_d = Current_Player;
  }
  if (Current_Player == 2) {
    Current_Comparer_d = Current_Player;
  }
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if(board[j + (i * width)] == Current_Comparer_d) {
        win_Count++;
        current_width = j;
        for (int k = j - 1 + width + (i * width); 
             current_width > 0  &&
             k < Board_Length; k = width + k - 1) {
          if (board[k] == Current_Comparer_d) {
            win_Count++;
            if (win_Count >= length) {
              is_Win = true;
              return true;
            } 
          } else {
            win_Count = 0;
          }
          current_width--;
        }
        win_Count = 0;
      }
    }
  }
  return false;
}

int play_connect(const int moves[], int width, int height, int length) {
  const int Player_Number1 = 1;
  const int Player_Number2 = 2;
  const int empty = 3;
  const int Board_Length = width * height;
  int Winning_Move = 0;
  bool Is_First_Player = true;
  bool Is_Game_Valid = true;
  int board[1024] = {0};
  for (int i = 0; i < Board_Length; i++) {
    board[i] = empty;
  }

  int Current_Move_Location = 0;
  int intial_Current_Move_Location = Current_Move_Location;
  int Current_Winning_Move = 0;
  int Current_Player = 0;
  for (int i = 0; i < Board_Length; i++)
  {
    Current_Move_Location = moves[i];
    intial_Current_Move_Location = Current_Move_Location;
    if (Is_First_Player) {
      Winning_Move = Winning_Move + 1;
      Is_First_Player = false;
      Current_Winning_Move = Winning_Move;
      Current_Player = Player_Number1;
    } else {
      Is_First_Player = true;
      Winning_Move = Winning_Move + 1;
      Current_Winning_Move = (Winning_Move * (-1));
      Current_Player = Player_Number2;
    }

    bool Is_Current_Turn = true;

    while (Is_Current_Turn && Current_Move_Location < Board_Length) {
      if (intial_Current_Move_Location < 0 ||
          intial_Current_Move_Location > width - 1) {
        Is_Game_Valid = false;
        break;
      }
      if (board[Current_Move_Location] == empty) {
        board[Current_Move_Location] = Current_Player;
        Is_Current_Turn = false;
      }
      else if (board[Current_Move_Location] == 1 || 
               board[Current_Move_Location] == 2) {
        Current_Move_Location = Current_Move_Location + width;

      }

      if (Current_Move_Location >= Board_Length) {
        Is_Game_Valid = false;
        break;
      }
    }

    if(Is_Game_Valid == false) {
      return wrong;
    }

    if (horizontal(Current_Player, width, height, length, board)) {
      return Current_Winning_Move;
    }
    if (vertical(Current_Player, width, height, length, board)) {
      return Current_Winning_Move;
    }
    if (diagonal_right(Current_Player, width, height, length, board)) {
      return Current_Winning_Move;
    }
    if (diagonal_left(Current_Player, width, height, length, board)) {
      return Current_Winning_Move;
    }
  }
  return tie;
}


