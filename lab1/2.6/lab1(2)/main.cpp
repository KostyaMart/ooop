#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Die {
public:
    virtual int roll() const = 0;
    virtual int getNumSides() const = 0;
    virtual double getProbability(int side) const = 0;
    virtual ~Die() {}
};

class NDie : public Die {
private:
    int sides;
    std::vector<double> probabilities;

public:
    NDie(int numSides) : sides(numSides) {
        setRandomProbabilities();
    }

    int roll() const override {
        double random = (rand() % 101) / 100.0;
        double cumulativeProbability = 0.0;

        for (int i = 0; i < sides; ++i) {
            cumulativeProbability += probabilities[i];
            if (random <= cumulativeProbability) {
                return i + 1;
            }
        }

        // Default return (shouldn't happen if probabilities are valid)
        return 1;
    }

    int getNumSides() const override {
        return sides;
    }

    double getProbability(int side) const override {
        return probabilities[side - 1];
    }

private:
    void setRandomProbabilities() {
        double totalProbability = 0.0;

        for (int i = 0; i < sides; ++i) {
            double random = (rand() % 101) / 100.0;
            totalProbability += random;
            probabilities.push_back(random);
        }

        // Нормализация вероятностей, чтобы они суммировались до 1
        for (int i = 0; i < sides; ++i) {
            probabilities[i] /= totalProbability;
        }
    }
};

class DiceSet {
private:
    std::vector<Die*> diceSet;

public:
    void addDie(Die* die) {
        diceSet.push_back(die);
    }

    std::vector<int> rollAll() const {
        std::vector<int> rolls;
        for (const auto& die : diceSet) {
            rolls.push_back(die->roll());
        }
        return rolls;
    }

    std::vector<std::pair<int, double>> getAllSumsAndProbabilities() const {
        std::vector<std::pair<int, double>> result;
        calculateSumsAndProbabilities(0, 0, 1.0, result);
        normalizeProbabilities(result);
        return result;
    }

    const std::vector<Die*>& getAllDice() const {
        return diceSet;
    }

    ~DiceSet() {
        for (auto it = diceSet.begin(); it != diceSet.end(); ++it) {
            delete *it;
        }
    }

private:
    void calculateSumsAndProbabilities(int index, int currentSum, double currentProbability, std::vector<std::pair<int, double>>& result) const {
        if (index == diceSet.size()) {
            for (auto& entry : result) {
                if (entry.first == currentSum) {
                    entry.second += currentProbability;
                    return;
                }
            }
            result.push_back(std::make_pair(currentSum, currentProbability));
        } else {
            for (int i = 1; i <= dynamic_cast<NDie*>(diceSet[index])->getNumSides(); ++i) {
                calculateSumsAndProbabilities(index + 1, currentSum + i, currentProbability * dynamic_cast<NDie*>(diceSet[index])->getProbability(i), result);
            }
        }
    }

    void normalizeProbabilities(std::vector<std::pair<int, double>>& result) const {
        double totalProbability = 0.0;
        for (const auto& entry : result) {
            totalProbability += entry.second;
        }

        for (auto& entry : result) {
            entry.second /= totalProbability;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));

    DiceSet diceSet;

    int numDice;
    std::cout << "Введите количество костей в наборе: ";
    std::cin >> numDice;

    for (int i = 0; i < numDice; ++i) {
        int numSides;
        std::cout << "Грани для кости " << i + 1 << " (2, 4, 6, 8, 10, 12, 20): ";
        std::cin >> numSides;

        NDie* die = new NDie(numSides);
        diceSet.addDie(die);

        std::cout << "Вероятности для кости " << i + 1 << " установлены." << std::endl;
    }

    std::vector<std::pair<int, double>> sumsAndProbabilities = diceSet.getAllSumsAndProbabilities();

    std::cout << "Все возможные суммы и их вероятности:" << std::endl;
    for (const auto& entry : sumsAndProbabilities) {
        std::cout << "Сумма: " << entry.first << ", Вероятность: " << entry.second << std::endl;
    }

    // Вывод вероятности выпадения каждой грани каждой кости
    std::cout << "Вероятности для каждой грани каждой кости:" << std::endl;
    for (const auto& die : diceSet.getAllDice()) {
        int numSides = die->getNumSides();
        std::cout << "Кость с " << numSides << " гранями:" << std::endl;

        for (int side = 1; side <= numSides; ++side) {
            std::cout << "Грань " << side << ": " << die->getProbability(side) << std::endl;
        }
    }

    return 0;
}
