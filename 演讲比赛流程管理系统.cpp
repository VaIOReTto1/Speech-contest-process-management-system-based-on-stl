#include<iostream>
#include"SpeechManager.h"
#include<ctime>

using namespace std;

int main(){
	srand((unsigned int)time(NULL));
	SpeechManager s1;

	int input;
	while (1){
		s1.Show_menu();
		cout << "            ���������ѡ�            " << endl;
		cin >> input;
		switch (input){
		case 0:
			s1.Exit_system();
			break;
		case 1:
			s1.Start_speech();
			break;
		case 2:
			s1.Show_record();
			break;
		case 3:
			s1.Clear_record();
			break;
		default:
			system("cls");//����
			break;
		}
	}

	system("pause");
	return 0;
}