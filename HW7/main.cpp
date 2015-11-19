#include <iostream>
#include "WriteCode.h"
#include "input.h"
#include "time.h"
using namespace std;

double checkHelper(int index, vector<string> str, int expectedResult, int diameter){
    clock_t start = clock();
    WriteCode sol;
    double score = 0;
    TreeNode* root = sol.RecoverTree(str);
    int res1 = sol.FindMaxPathSum(root);
    int res2 = sol.TreeDiameter(root);
    clock_t end = clock();
    double duration = static_cast<double>(end-start)/CLOCKS_PER_SEC * 1000;
    cout << "run " << static_cast<double>(end-start)/CLOCKS_PER_SEC * 1000 << "ms\n";
    if (res1 == expectedResult) {
        score += 0.5;
    }
    if(res2 == diameter){
        score += 0.5;
    }
    if( duration > 2 && duration <= 4){
        cout << "A little time exceed, this will decrease some score\n";
        score *= 0.5;
    }
    else if(duration > 4 && duration <= 6){
        cout << "More time exceeded, this will decrease some score\n";
        score *= 0.3;
    }
    else if(duration > 6){
        cout << "Time exceeded, no score";
        score *= 0;
    }
    if(res1 != expectedResult || res2!=diameter){
        cout << "**FAIL TEST " << index << "**" << endl;
        cout << "The Tree is \n" ;
        for(string item : str){
            cout << item << " ";
        }
        cout << endl;
        cout << "The expected Diameter: " << diameter << ", Your answer: " <<  res2 << endl;
        cout << "The expected Sum: " << expectedResult << ", Your answer: " <<  res1 << endl;
        return score;
    }
    cout << "**PASS TEST " << index <<"**" << endl;
    return score;
}
void check(){
    double score = 0;
    score += checkHelper(1,str1,6,3);
    score += checkHelper(2,str2,15,5);
    score += checkHelper(3,str3,9,5);
    score += checkHelper(4,str4,-4,4);
    score += checkHelper(5,str5,7317,22);
    score += checkHelper(6,str6, 3330,25);
    score += checkHelper(7,str7, 11794,50);
    score += checkHelper(8,str8, 16022,49);
    //print score
    cout << endl << "Your score: " << score << "/8" << endl;
}

int main()
{
    check();
    return 0;
}
