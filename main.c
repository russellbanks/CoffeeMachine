#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

struct CoffeeMachine {
    int waterCapacityMl;
    enum {ON, OFF} power;
    int waterMl;
    int beansGrams;
    int milkMl;
};

typedef struct CoffeeMachine CoffeeMachine;

struct CoffeeDrink {
    char name[20];
    int waterNeededMl;
    int beansNeededGrams;
    int milkNeededMl;
};

typedef struct CoffeeDrink CoffeeDrink;

struct CoffeeDrink BasicCoffee = {"Basic Coffee", 50, 10, 0};

struct CoffeeDrink Espresso = {"Espresso", 30, 10, 0};

struct CoffeeDrink Latte = { "Latte", 200, 24, 150};

struct CoffeeDrink Cappuccino = { "Cappuccino", 250, 18, 100};

CoffeeMachine makeCoffeeMachine(int waterCapacityMl);

CoffeeDrink convertChoiceToDrink(int choice);

void fillWater(CoffeeMachine *pMachine);

void fillBeans(CoffeeMachine *pMachine);

void fillMilk(CoffeeMachine *pMachine);

void turnOn(CoffeeMachine *pMachine);

void createCoffeeDialogs(CoffeeMachine *pMachine);

int main() {
    CoffeeMachine coffeeMachine = makeCoffeeMachine(1000);
    fillWater(&coffeeMachine);
    fillBeans(&coffeeMachine);
    fillMilk(&coffeeMachine);
    if (coffeeMachine.power == OFF) turnOn(&coffeeMachine);
    createCoffeeDialogs(&coffeeMachine);
    return 0;
}

CoffeeMachine makeCoffeeMachine(int waterCapacityMl) {
    CoffeeMachine machine = {waterCapacityMl, OFF, 0, 0, 0};
    puts("Created coffee machine");
    return machine;
}

void fillWater(CoffeeMachine *machine) {
    int waterMl = 0;
    printf("The coffee machine has a tank capacity of %dml\n", machine->waterCapacityMl);
    printf("You can add up to %dml\n", machine->waterCapacityMl - machine->waterMl);
    while (waterMl <= 0 || waterMl > machine->waterCapacityMl - machine->waterMl) {
        puts("How much water do you want to add?");
        scanf("%d", &waterMl);
        if (machine->waterCapacityMl < machine->waterMl + waterMl) {
            printf("You can't add more water than the tank can hold (%dml > %dml)\n", waterMl, machine->waterCapacityMl - machine->waterMl);
        }
    }
    printf("Adding %dml of water to the water tank\n", waterMl);
    machine->waterMl += waterMl;
    int percentFull = (machine->waterMl * 100) / machine->waterCapacityMl;
    printf("The water tank is %d%% full (%dml/%dml) \n", percentFull, machine->waterMl, machine->waterCapacityMl);
}

void fillBeans(CoffeeMachine *machine) {
    int beansGrams = 0;
    puts("How many grams of coffee beans do you want to add?");
    scanf("%d", &beansGrams);
    printf("Adding %d grams of coffee beans\n", beansGrams);
    machine->beansGrams += beansGrams;
    printf("The coffee machine has %d grams of coffee beans\n", machine->beansGrams);
}

void fillMilk(CoffeeMachine *machine) {
    int milkMl = 0;
    puts("How much milk do you want to add?");
    scanf("%d", &milkMl);
    printf("Adding %dml of milk\n", milkMl);
    machine->milkMl += milkMl;
    printf("The coffee machine has %dml of milk\n", machine->milkMl);
}

void turnOn(CoffeeMachine *machine) {
    machine->power = ON;
    puts("The coffee machine is now on");
}

void turnOff(CoffeeMachine *machine) {
    machine->power = OFF;
    puts("The coffee machine is now off");
}

_Bool makeCoffee(CoffeeMachine *pMachine, CoffeeDrink coffee) {
    if (pMachine->waterMl < coffee.waterNeededMl) {
        printf("Not enough water to make a %s\n", coffee.name);
        return false;
    }
    if (pMachine->beansGrams < coffee.beansNeededGrams) {
        printf("Not enough water to make a %s\n", coffee.name);
        return false;
    }
    if (pMachine->milkMl < coffee.milkNeededMl) {
        printf("Not enough water to make a %s\n", coffee.name);
        return false;
    }
    pMachine->waterMl -= coffee.waterNeededMl;
    pMachine->beansGrams -= coffee.beansNeededGrams;
    pMachine->milkMl -= coffee.milkNeededMl;
    printf("Your %s is ready!\n", coffee.name);
    return true;
}

void reportIngredientsQuantity(CoffeeMachine *pMachine) {
    puts("");
    puts("The coffee machine has:");
    printf("Water: %dml\n", pMachine->waterMl);
    printf("Beans: %d grams\n", pMachine->beansGrams);
    printf("Milk: %dml\n", pMachine->milkMl);
    puts("");
}

void createCoffeeDialogs(CoffeeMachine *pMachine) {
    int coffeeChoice = 0;
    while (coffeeChoice != 1 && coffeeChoice != 2 && coffeeChoice != 3) {
        puts("What coffee would you like to make?");
        puts("1. Espresso");
        puts("2. Latte");
        puts("3. Cappuccino");
        printf("Enter your choice: ");
        scanf("%d", &coffeeChoice);
        if (coffeeChoice != 1 && coffeeChoice != 2 && coffeeChoice != 3) {
            puts("Invalid choice\n");
        }
    }
    int coffeeMadeSuccessfully = makeCoffee(pMachine, convertChoiceToDrink(coffeeChoice));
    if (coffeeMadeSuccessfully != true) reportIngredientsQuantity(pMachine);
    char continueChoice;
    printf("Would you like to make another coffee? (y/n): ");
    scanf(" %c", &continueChoice);
    if (tolower(continueChoice) == 'y') {
        createCoffeeDialogs(pMachine);
    } else {
        turnOff(pMachine);
    }
}

CoffeeDrink convertChoiceToDrink(int coffeeChoice) {
    switch (coffeeChoice) {
        case 1:
            return Espresso;
        case 2:
            return Latte;
        case 3:
            return Cappuccino;
        default:
            return BasicCoffee;
    }
}
