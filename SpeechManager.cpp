#include "SpeechManager.h"

SpeechManager::SpeechManager(){
	this->Init_speaker();
	this->Create_speaker();
	this->Load_record();
}

SpeechManager::~SpeechManager(){
}

void SpeechManager::Show_menu(){
	cout << "                                      " << endl;
	cout << "            ��ӭ�μ��ݽ�����!         " << endl;
	cout << "            1.��ʼ�ݽ�����            " << endl;
	cout << "            2.�鿴�����¼            " << endl;
	cout << "            3.��ձ�����¼            " << endl;
	cout << "            0.�˳���������            " << endl;
	cout << "                                      " << endl;
}

void SpeechManager::Exit_system(){
	cout << "            ��ӭ�´�ʹ��            " << endl;
	system("pause");
	exit(0);
}

void SpeechManager::Init_speaker(){
	//��ʼ��ѡ������
	this->v1.clear();
	this->v2.clear();
	this->third.clear();
	this->speaker.clear();
	this->record.clear();

	this->rounds = 1;//��ʼ�������ִ�
}

void SpeechManager::Create_speaker(){
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++){
		string name = "ѡ��";
		name += nameSeed[i];

		Speaker s;
		s.Name = name;
		for (int j = 0; j < 2; j++) s.Score[j] = 0;

		this->v1.push_back(10001 + i);
		this->speaker.insert(make_pair(10001 + i, s));
	}
}

void SpeechManager::Start_speech(){
	//��һ�ֱ���
	//��ǩ
	this->Drawing();
	//����
	this->Completion();
	//��ʾ�����ɹ�
	this->Show_score();
	//�ڶ��ֱ���
	this->rounds++;
	//��ǩ
	this->Drawing();
	//����
	this->Completion();
	//��ʾ���ս��
	this->Show_score();
	//�������
	this->Record();

	//���ñ���
	this->Init_speaker();
	this->Create_speaker();
	this->Load_record();

	cout << "�������˳������" << endl;
	system("pasue");
	system("cls");
}

void SpeechManager::Drawing(){
	if (this->rounds == 1) cout << "            ��һ�ֱ���ѡ�����ڳ�ǩ" << endl;
	else cout << "            �ڶ��ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------------------------" << endl;
	cout << "            �ݽ�˳������" << endl;
	if (this->rounds == 1){
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) cout << *it << " ";
		cout << endl;
	}
	else{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) cout << *it << " ";
		cout << endl;
	}
	cout << "-------------------------------------" << endl;
	system("pause");
	cout << endl;
}

void SpeechManager::Completion(){
	if (this->rounds == 1) cout << "            ��һ�ֱ�����ʽ��ʼ" << endl;
	else cout << "            �ڶ��ֱ�����ʽ��ʼ" << endl;

	multimap<double, int, greater<double>>group;//��¼ÿ��ѡ������
	int num = 0;//6��Ϊһ��

	vector<int>v;
	if (this->rounds == 1) v = v1;
	else v = v2;

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++){
		num++;

		deque<double>d;//��ŷ���
		for (int i = 0; i < 10; i++){
			double score = (rand() % 401 + 600) / 10.f; //600~1000
			d.push_back(score);
		}

		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();//ȥ����߷�
		d.pop_back();//ȥ����ͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0f);//�����ܷ�
		double avg = sum / (double)d.size();//����ƽ����
		this->speaker[*it].Score[this->rounds - 1] = avg;

		group.insert(make_pair(avg, *it));
		//6��һ��
		if (num % 6 == 0){
			if (num / 6 == 1) cout << "��һС������������£�" << endl;
			else cout << "�ڶ�С������������£�" << endl;
			for (multimap<double, int, greater<double>>::iterator it = group.begin(); it != group.end(); it++)
				cout << "��ţ�" << it->second << " ������" << this->speaker[it->second].Name
				<< " �ɼ���" << this->speaker[it->second].Score[this->rounds - 1] << endl;

			//ȡ����ǰ����
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = group.begin(); it != group.end() && count < 3; it++, count++){
				if (this->rounds == 1) v2.push_back((*it).second);
				else third.push_back((*it).second);
			}

			group.clear();
			cout << endl;
		}
	}
	if (this->rounds == 1) cout << "            ��һ�ֱ������" << endl;
	else cout << "            �ڶ��ֱ������" << endl;

	system("pause");
}

void SpeechManager::Show_score(){
	if (this->rounds == 1) cout << "            ��һ�ֱ�������ѡ����Ϣ���£�" << endl;
	else cout << "            �ڶ��ֱ�������ѡ����Ϣ���£�" << endl;

	vector<int>v;
	if (this->rounds == 1) v = v2;
	else v = third;

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		cout << "��ţ�" << *it<< " ������" <<this-> speaker[*it].Name
		<< " �ɼ���" << this->speaker[*it].Score[this->rounds - 1] << endl;
    cout << endl;

	system("pause");
	system("cls");
	this->Show_menu();
}

void SpeechManager::Record(){
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = third.begin(); it != third.end(); it++)
		ofs << *it << "," << speaker[*it].Score[1] << ",";
	ofs <<endl;

	ofs.close();
	cout << "��¼�ѱ���" << endl;
	this->File_is_empty = false;
}

void SpeechManager::Load_record(){
	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open()){
		this->File_is_empty = true;
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()){
		cout << "�ļ�Ϊ�գ�" << endl;
		this->File_is_empty = true;
		ifs.close();
		return;
	}

	this->File_is_empty = false;

	ifs.putback(ch);//�Ѷ�ȡ�ĵ����ַ��Ż�ȥ

	string data;
	int index = 0;
	while (ifs >> data){
		vector<string>v;

		int pos = -1;
		int start = 0;
		
		while (true){
			pos = data.find(",", start);
			if (pos == -1) break;
			string tmp = data.substr(start, pos - start);//��һ������ʼλ�ã��ڶ����ǵ����ŵĽ�ȡ����
			v.push_back(tmp);
			start = pos + 1;
		}
		this->record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
}

void SpeechManager::Show_record(){
	if (this->File_is_empty) cout << "�ļ������ڣ����¼Ϊ�գ�" << endl;
	else{
		for (map<int, vector<string>>::iterator it = this->record.begin(); it != this->record.end(); it++){
			cout << "��" << it->first+1 << "��" <<
				"�ھ���ţ�" << it->second[0] << " �÷֣�" << it->second[1] << " "
				"�Ǿ���ţ�" << it->second[2] << " �÷֣�" << it->second[3] << " "
				"������ţ�" << it->second[4] << " �÷֣�" << it->second[5] << endl;
		}
	}
	system("pause");
	system("cls");
}

void SpeechManager::Clear_record()
{
	cout << "ȷ����գ�" << endl
		<< "1. Yes" << endl
		<< "2. No" << endl;

	int select;
	cin >> select;

	if (select == 1){
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		this->Init_speaker();
		this->Create_speaker();
		this->Load_record();

		cout << "����ɹ�" << endl;
	}
	else if (select == 2) return;
	else cout << "��������" << endl;

	system("pause");
	system("cls");
}