#include <Test.h>
#include <assert.h>
#include <iostream>
#include "../../AutoFocus/daten.h"

using namespace std;

void testDefaultCtor()
{
  cout << "Test wird durchgeführt" << endl;
  Daten o;
  QComboBox a;
  a.addItem("test", 3);

  assert(3 == o.getBrennweite(&a));
  cout << "Test wurde ausgeführt" << endl;
}
