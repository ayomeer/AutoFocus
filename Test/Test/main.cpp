#include <Test.h>
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  testDefaultCtor();

  cout << "Test erfolgreich" << endl;
}
