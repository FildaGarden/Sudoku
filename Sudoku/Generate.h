bool unUsedInBox(int rowStart, int colStart, int num);
bool unUsedInRow(int i, int num);
bool unUsedInCol(int j, int num);
bool checkIfSafe(int i, int j, int num);
void fillBox(int row, int col);
void fillDiagonal();
bool fillRemaining(int i, int j);
void printSudoku();
void removeDigits();
void saveGame();
int fillValues(int k);

