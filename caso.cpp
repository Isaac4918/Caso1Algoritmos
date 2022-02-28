#include <stdio.h>
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//========================================================== Compare the triplets ============================================================
void compareTrip1(){
    
    int a[] =  {4, 2, 1};
    int b[] =  {4, 1, 3};

    int puntajeA = 0;
    int puntajeB = 0;

    for(int i = 0; i<3; i++){
        if (a[i] > b[i]){
            puntajeA++;
        }
        else if(a[i] < b[i]){
            puntajeB++;
        }
    }

    cout << puntajeA << " " << puntajeB << endl;
}

/*
Esta implementacion varia en que en lugar de realizar un ciclo donde vaya uno a uno de los elementos de las listas
compara linealmente cada elemento y hace la sumatoria de puntajes respectiva
*/
void compareTrip2(){
    
    int a[] =  {4, 2, 1};
    int b[] =  {4, 1, 3};

    int puntajeA = 0;
    int puntajeB = 0;
    
    if (a[0] != b[0]){
        int numero = (a[0] - b[0])/abs(a[0] - b[0]);
        puntajeA+= numero + 1;
        puntajeB+= numero - 1;
    }
    if (a[1] != b[1]){
        int numero = (a[1] - b[1])/abs(a[1] - b[1]);
        puntajeA+= numero + 1;
        puntajeB+= numero - 1;
    }
    if (a[2] != b[2]){
        int numero = (a[2] - b[2])/abs(a[2] - b[2]);
        puntajeA+= numero + 1;
        puntajeB+= numero - 1;
    }

    puntajeA = puntajeA/2;
    puntajeB = abs(puntajeB/2);

    cout << puntajeA << " " << puntajeB << endl;
}

//========================================================== Time Conversion ============================================================

string timeConver1(string formatAP) {
	string format24h = formatAP.substr(2, 6); //:mm:ss
	int hrs = stoi(formatAP.substr(0,2)); //hh

	if(hrs==12){
		if(formatAP[8]=='A')
			hrs = 0; //Medianoche 00:mm:ss
	}else if(formatAP[8]=='P'){
		hrs += 12; //Horas de la tarde (13-23)
	}

	format24h = (hrs<10) ? "0"+to_string(hrs)+format24h : to_string(hrs)+format24h;

	return format24h;
}

/*
esta implementacion es mejor ya que en lugar de hacer 2 comparaciones hace solo 1 y hace una conversion de forma mas rapida
*/
string timeConver2(string formatAP) {
	string format24h = formatAP.substr(2, 6); //:mm:ss
	int hrs = stoi(formatAP.substr(0,2)); //hh
	int factor = ((hrs%12)/hrs); //Para PM: =0 si hrs=12 | =1 en otro caso
	
	if(formatAP[8]=='A')
        factor--; //Para AM: =-1 si hrs=12 | =0 en otro caso 
	
    hrs += (12 * factor);

	format24h = (hrs<10) ? "0"+to_string(hrs)+format24h : to_string(hrs)+format24h;
	
	return format24h;

}

//========================================================== Subarray Division ============================================================



//========================================================== Minion Game ============================================================
void the_minion_game(string palabra){
    //puntaje[0] Kevin
    //puntaje[1] Stuart
    int puntaje[2]={0,0};

    //BANANA
    for(int contador=0;contador<palabra.length();contador++){
        puntaje[0]+=((palabra[contador]=='A'||palabra[contador]=='E'||palabra[contador]=='I'||palabra[contador]=='O'||palabra[contador]=='U')?
                        palabra.length()-contador:0);
        puntaje[1]+=((palabra[contador]!='A'&&palabra[contador]!='E'&&palabra[contador]!='I'&&palabra[contador]!='O'&&palabra[contador]!='U')?
                        palabra.length()-contador:0);
    }

    if(puntaje[0]>puntaje[1]){
        cout<<"Kevin "<<puntaje[0]<<endl;
    }
    else if(puntaje[0]<puntaje[1]){
        cout<<"Stuart "<<puntaje[1]<<endl;
    }
    else{
        cout<<"Draw"<<endl;
    }
}


//========================================================== Cipher ============================================================

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

string cipher(int k, int n, string s) {
//    /* n es la longitud del string resultado
//        Calcular n utilizando k y la longitud de s */
//    int n = s.size()-(k-1);
    vector<char> result(n);

    result[0] = s[0]-48;

    // Calcular los elementos de 1 a k-1
    for (int i = 1; i < k; i++) {
        result[i] = s[i-1] ^ s[i];
    }

    // Calcular los elementos de k en adelante
    char aux;
    for (int i = k; i < n; i++) {
        aux = '0';
        for (int j = i-(k-1); j < i; j++) {
            aux = aux ^ result[j];
        }
        result[i] = aux ^ s[i];
    }

    // Armar el string con el resultado
    string final_result = "";
    for (int i = 0; i < n; i++) {
        final_result += result[i]+48;
    }
    return final_result;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

//========================================================== Pairs ============================================================

int pairs_with_pointers(int k, vector<int> arr) {
    
    // Ordenar el array(ascendente)
    sort(arr.begin(), arr.end());
    
    // {Pointer 2, NULL, Pointer1}
    int pointers[] = {1, 0, 0};
    int result = 0;
    int valueDif = 0;
    
    while (pointers[0] < arr.size()) {
        
        valueDif = arr[pointers[0]] - arr[pointers[2]];
        
        // Si es lo que busco, aumento pointer2
        if (valueDif == k) {
            result++;
            pointers[0]++;
            continue;
        }
        
        // Mueve el puntero necesario dependiendo si es mayor o menor
        pointers[ ((valueDif - k)/abs(valueDif - k)) + 1 ]++;
    }
    
    return result;
}


//===================================================== MAIN ===================================================================

int main(){
    cout << "==============Compare Triplets 1=================" << endl;
    compareTrip1();

    cout << "==============Compare Triplets 2=================" << endl;

    compareTrip2();

    cout << "==============Time Converter 1==================" << endl;

    cout << timeConver1("12:41:15AM") << endl;
	cout << timeConver1("08:41:15PM") << endl;

    cout << "==============Time Converter 2==================" << endl;

	cout << timeConver2("12:41:15AM") << endl;
	cout << timeConver2("08:41:15AM") << endl;

    cout << "==============" << endl;



    cout << "============== Minion Game ===========================" << endl;

    string palabra1="BANANA", palabra2="ARIAL", palabra3="POO";

    the_minion_game(palabra1);
    //the_minion_game(palabra2);
    //the_minion_game(palabra3);

    cout << "============== Pairs ================================" << endl;

    vector<int> arr1 = {1, 3, 5, 8, 6, 4, 2};
    vector<int> arr2 = {1, 5, 3, 4, 2};


    cout << "Resultado: " << pairs_with_pointers(2, arr1) << endl;
    cout << "Resultado: " << pairs_with_pointers(2, arr2) << endl;

    cout << "==============" << endl;


    cout << "============== Cipher ===========================" << endl;
    cout << "Ingrese lo que desea cifrar:" << endl;

    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string s;
    getline(cin, s);

    string result = cipher(k, n, s);

    cout << "Resultado = " << result << "\n";
    

    return 0;

}