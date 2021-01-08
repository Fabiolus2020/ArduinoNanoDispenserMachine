//created by Fabiolus 2021/01/08
//the_fabiolous@hotmail.com

String UserItem;
int  UserItemCount;
String UserConfirmation;
String InvCheck;
int RedLedPin = 2;
int YellowLedPin = 3;
int WhiteLedPin = 4;
int GreenLedPin = 5;


void ClearScreen() {
  for (int counter = 1; counter <= 15; counter++ ) {
    Serial.println(" ");
  }
}

void EndProgram() {
  Serial.println ("Thank You for using Fabiolus dispenser machine");
  for (int counter = 1; counter <= 10; counter++)
  {
    digitalWrite(RedLedPin, HIGH);
    delay(100);
    digitalWrite(RedLedPin, LOW);
    delay(100);
    digitalWrite(GreenLedPin, HIGH);
    delay(100);
    digitalWrite(GreenLedPin, LOW);
    delay(100);
  }
}


void DispencingItem() {
  Serial.println(UserItemCount);
  for (int counter = 1; counter <= UserItemCount; counter++)
  {
    digitalWrite(GreenLedPin, HIGH);
    delay(500);
    digitalWrite(GreenLedPin, LOW);
    delay(500);
  }
}

void InvalidInput() {
  for (int counter = 1; counter <= 5; counter++)
  {
    digitalWrite(RedLedPin, HIGH);
    delay(100);
    digitalWrite(RedLedPin, LOW);
    delay(100);
  }
  Serial.println ("Invalid Input, try again");

}

void NotenoughInv() {
  for (int counter = 1; counter <= 5; counter++)
  {
    digitalWrite(RedLedPin, HIGH);
    delay(100);
    digitalWrite(RedLedPin, LOW);
    delay(100);
  }
  Serial.println ("Not enough inventory");

}

void InventoryProcess() {
  int appleInventory = 10;
  int bananaInventory = 10;
  int bottleOfWaterInventory = 10;


  for (int counter = 1; counter <= UserItemCount; counter++)


    if (UserItemCount > appleInventory) {
      // ClearScreen();
      NotenoughInv();
      InvCheck = "fail";
      return InvCheck;
    }
    else if (UserItemCount <= appleInventory) {
      ClearScreen();
      InvCheck = "pass";
      return InvCheck;
    }

  if (UserItemCount > bananaInventory) {
    // ClearScreen();
    NotenoughInv();
    InvCheck = "fail";
    return InvCheck;
  }
  else if (UserItemCount <= bananaInventory) {
    ClearScreen();
    InvCheck = "pass";
    return InvCheck;
  }

  if (UserItemCount > bottleOfWaterInventory) {
    //ClearScreen();
    NotenoughInv();
    InvCheck = "fail";
    return InvCheck;
  }
  else if (UserItemCount <= bottleOfWaterInventory) {
    ClearScreen();
    InvCheck = "pass";
    return InvCheck;
  }

}



void PinModeOutput () {
  pinMode(GreenLedPin, OUTPUT);
  pinMode(YellowLedPin, OUTPUT);
  pinMode(WhiteLedPin, OUTPUT);
  pinMode(RedLedPin, OUTPUT);
}

void PinModeLow () {
  digitalWrite(GreenLedPin, LOW);
  digitalWrite(YellowLedPin, LOW);
  digitalWrite(WhiteLedPin, LOW);
  digitalWrite(RedLedPin, LOW);
}

void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  PinModeOutput();
  PinModeLow();

}

void loop() {


  // put your main code here, to run repeatedly:
step1:
  Serial.flush();
  ClearScreen();
  Serial.println("////////////////////////////////////////////////////");
  Serial.println("                                                    ");
  Serial.println(" input item of choice                                ");
  Serial.println(" Choice are :                                       ");
  Serial.println("            apple                                   ");
  Serial.println("            banana                                  ");
  Serial.println("            bottle of water                         ");
  Serial.println("                                                    ");
  Serial.println("////////////////////////////////////////////////////");

  while (Serial.available() == 0); {}
  UserItem = Serial.readStringUntil('\n');
  UserItem.trim();

  if (UserItem.equals("apple")) {
    goto step2;
  }

  if (UserItem.equals("banana")) {
    goto step2;
  }

  if (UserItem.equals("bottle of water")) {
    goto step2;
  }
  else {
    InvalidInput();
    goto step1;
  }


step2:
  ClearScreen();
  Serial.println("////////////////////////////////////////////////////");
  Serial.println("                                                    ");
  Serial.print(" How many "                                            );
  Serial.print(UserItem);
  Serial.println(" would you like?                                    ");
  Serial.println("                                                    ");

  Serial.println("////////////////////////////////////////////////////");

  while (Serial.available() == 0); {}
  UserItemCount = Serial.parseInt();

  if (UserItemCount == 0) {
    InvalidInput();
    goto step2;
  }

  InventoryProcess();


  if (InvCheck == "fail") {
    goto step2;
  }

  if (InvCheck == "pass") {

    goto step3;
  }

step3:
  Serial.println("////////////////////////////////////////////////////");
  Serial.println("                                                    ");
  Serial.print(" You need "                                            );
  Serial.print(UserItemCount);
  Serial.print(" "                                                     );
  Serial.println(UserItem);
  Serial.println(" Are you sure?                                       ");
  Serial.println("////////////////////////////////////////////////////");

  while (Serial.available() == 0); {}
  String UserConfirm = Serial.readStringUntil('\n');


  if (UserConfirm == "yes") {

    DispencingItem();
    delay(2000);
    EndProgram();
  } else if (UserConfirm == "no") {
    goto step2;
  } else {
    InvalidInput();
    ClearScreen();
    goto step3;
  }

}
