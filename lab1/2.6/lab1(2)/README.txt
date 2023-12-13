Класи:

Die (абстрактний клас)
NDie (похідний клас від Die)
DiceSet
Методи:

В класі Die:

virtual int roll() const
virtual int getNumSides() const
virtual double getProbability(int side) const
virtual ~Die() {}
В класі NDie (похідний від Die):

int roll() const override
int getNumSides() const override
double getProbability(int side) const override
private: void setRandomProbabilities()
В класі DiceSet:

void addDie(Die* die)
std::vector<int> rollAll() const
std::vector<std::pair<int, double>> getAllSumsAndProbabilities() const
const std::vector<Die*>& getAllDice() const
~DiceSet()
private: void calculateSumsAndProbabilities(...)
private: void normalizeProbabilities(...)
Головна функція main():

Запит користувача на введення кількості та граней кожної кості в наборі.
Створення об'єкта DiceSet.
Заповнення DiceSet кількома об'єктами NDie.
Виведення всіх можливих сум та їх ймовірностей.
Виведення ймовірностей кожної грані кожної кості.
Загальна кількість елементів:

Класи: 3
Методи: 14 (включаючи конструктори, деструктори та вказані private-методи)
Функція main(): 1 (головна функція програми)