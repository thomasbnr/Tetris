#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sprite.hpp"
#include "Bloc.hpp"
#include "Board.hpp"

using namespace std;

class Display{

private:

  sf::Font font;
  float screenW = 1280;
  float screenH = 720;
  int menuChoice=1;


  //hotkeys:
  bool up=false;
  bool down=false;
  bool left=false;
  bool right=false;
  bool space=false;


  //SPRITES
  Sprite spriteTetris=Sprite("tetris", this->screenW, this->screenH);
  Sprite spritePhrase=Sprite("phrase",this->screenW,this->screenH);
  Sprite spriteSettings=Sprite("settings",this->screenW, this->screenH);
  Sprite spriteRules=Sprite("rules", this->screenW,this->screenH);
  Sprite spriteSure=Sprite("exit",this->screenW, this->screenH);
  Sprite spriteGuide=Sprite("guide",this->screenW, this->screenH);
  Sprite spritePlus=Sprite("plus", this->screenW, this->screenH);
  Sprite spriteMoins=Sprite("moins", this->screenW,this->screenH);
  Sprite spriteGood=Sprite("good",this->screenW,this->screenH);
  Sprite spriteRead=Sprite("read",this->screenW,this->screenH);
  Sprite spriteBackRules=Sprite("back_rules",this->screenW, this->screenH);
  Sprite adilPixel=Sprite("adilPixel",this->screenW,this->screenH);
  Sprite thomasPixel=Sprite("thomasPixel",this->screenW, this->screenH);
  Sprite miniHeadAdil=Sprite("adilPixel",this->screenW,this->screenH);
  Sprite miniHeadThomas=Sprite("thomasPixel",this->screenW, this->screenH);
  Sprite miniHeadAdil2=Sprite("adilPixel",this->screenW,this->screenH);
  Sprite miniHeadThomas2=Sprite("thomasPixel",this->screenW, this->screenH);
  Sprite adilReal=Sprite("adilReal",this->screenW,this->screenH);
  Sprite thomasReal=Sprite("thomasReal",this->screenW, this->screenH);



public:

  //introduction
  Sprite tamtam=Sprite("tamtam", this->screenW, this->screenH);

  bool escape=false;

  //miniHead
  bool boom=false;
  bool head=false;

  bool push=false;//display if key pushed
  bool gameInitialised=false;
  //MENUS
  bool mainMenu=false;
  bool sure=false;
  bool rules=false;
  bool start=false;
  bool game=false;
  bool end=false;


  //gameMode
  int boardH=50;
  int boardW=50;
  int boardType=1;
  int pickType=1;
  bool blocPossible=false;
  bool difficultyIncrease=false;
  int gameMode=1;// 1 : normal / 2 : + bloc avant score / 3 : survie

  //game
  //->bloc
  bool selectedPiece=false;
  uint piece=0;

  //->board
  bool place=false;
  int selectedX;
  int selectedY;

  //mode de jeu
  int life=3;
  long score=0;
  int scoreMultiplier=1;
  int blocNumber=0;
  int minute=0;
  int seconde=0;
  int scorePerSec=2;

  //WINDOW
  sf:: RenderWindow mainWindow;

  //music
  bool menuLoop=false;
  bool gameLoop=false;
  sf::Music menuTheme;
  sf::Music gameTheme;

  //sound
  sf::SoundBuffer menuArrowBuffer;
  sf::Sound menuArrow;
  sf::SoundBuffer menuSpaceBuffer;
  sf::Sound menuSpace;
  sf::SoundBuffer blocDestructionBuffer;
  sf::Sound blocDestruction;
  sf::SoundBuffer lineDestructionBuffer;
  sf::Sound lineDestruction;
  sf::SoundBuffer changeBlocBuffer;
  sf::Sound changeBloc;
  sf::SoundBuffer errorBlocBuffer;
  sf::Sound errorBloc;
  sf::SoundBuffer moveBoardBuffer;
  sf::Sound moveBoard;
  sf::SoundBuffer setBlocBuffer;
  sf::Sound setBloc;
  sf::SoundBuffer tamtamSoundBuffer;
  sf::Sound tamtamSound;

  //intro
  bool intro=true;
  bool real=true;

////////////////////////////GLOBAL//////////////////////////////////////////////
  void init_window(){

    this->mainWindow.create(sf::VideoMode(this->screenW, this->screenH), "Tetris");
    this->mainWindow.setPosition(sf::Vector2i(200,100));
    this->mainWindow.setFramerateLimit(60);
    this->mainWindow.setKeyRepeatEnabled(false);
    //load font
    if(!this->font.loadFromFile("./ressources/font/arial.ttf"))
      cout<<"ERROR loading font"<<endl;

    //load music
    if(!menuTheme.openFromFile("./ressources/music/menu.ogg"))
      cout<<"ERROR loading menuTheme"<<endl;
    if(!gameTheme.openFromFile("./ressources/music/game.ogg"))
      cout<<"ERROR loading gameTheme"<<endl;

    //load sound
    if (!menuArrowBuffer.loadFromFile("./ressources/sound/menuArrow.ogg"))
      cout<<"ERROR loading menuArrowSound"<<endl;
    else
      menuArrow.setBuffer(menuArrowBuffer);

    if (!menuSpaceBuffer.loadFromFile("./ressources/sound/menuSpace.ogg"))
      cout<<"ERROR loading menuArrowSound"<<endl;
    else
      menuSpace.setBuffer(menuSpaceBuffer);

    if (!blocDestructionBuffer.loadFromFile("./ressources/sound/blocDestruction.wav"))
      cout<<"ERROR loading menuArrowSound"<<endl;
    else{
      blocDestruction.setBuffer(blocDestructionBuffer);
      blocDestruction.setVolume(4.00f);
    }


    if (!lineDestructionBuffer.loadFromFile("./ressources/sound/lineDestruction.wav"))
      cout<<"ERROR loading menuArrowSound"<<endl;
    else{
      lineDestruction.setBuffer(lineDestructionBuffer);
      lineDestruction.setVolume(5.00f);
    }

    if (!changeBlocBuffer.loadFromFile("./ressources/sound/changeBloc.wav"))
      cout<<"ERROR loading menuArrowSound"<<endl;
    else{
      changeBloc.setBuffer(changeBlocBuffer);
      changeBloc.setVolume(5.00f);
    }

    if (!errorBlocBuffer.loadFromFile("./ressources/sound/errorBloc.wav"))
      cout<<"ERROR loading menuArrowSound"<<endl;
    else{
      errorBloc.setBuffer(errorBlocBuffer);
      errorBloc.setVolume(20.00f);
    }

    if (!moveBoardBuffer.loadFromFile("./ressources/sound/moveBoard.wav"))
      cout<<"ERROR loading menuArrowSound"<<endl;
    else{
      moveBoard.setBuffer(moveBoardBuffer);
    }

    if (!setBlocBuffer.loadFromFile("./ressources/sound/setBloc.wav"))
      cout<<"ERROR loading menuArrowSound"<<endl;
    else{
      setBloc.setBuffer(setBlocBuffer);
      setBloc.setVolume(60.00f);
    }

    if(!tamtamSoundBuffer.loadFromFile("./ressources/sound/tamtamSound.wav"))
      cout<<"ERROR loading tamtamSound"<<endl;
    else{
      tamtamSound.setBuffer(tamtamSoundBuffer);
      tamtamSound.setVolume(150.00f);
    }

    //minihead

    this->miniHeadAdil.sprite.scale(0.3f, 0.3f);
    this->miniHeadAdil.sprite.setPosition(sf::Vector2f(screenW/20,screenH/16+this->screenH/30));
    this->miniHeadThomas.sprite.scale(0.3f, 0.3f);
    this->miniHeadThomas.sprite.setPosition(sf::Vector2f(screenW/2+screenW/7,screenH/16+this->screenH/30));

    this->miniHeadAdil2.sprite.scale(0.4f, 0.4f);
    this->miniHeadAdil2.sprite.setPosition(sf::Vector2f(screenW/20,screenH/16+this->screenH/30));
    this->miniHeadThomas2.sprite.scale(0.4f, 0.4f);
    this->miniHeadThomas2.sprite.setPosition(sf::Vector2f(screenW/2+screenW/7,screenH/16+this->screenH/30));
  }

  void event_manage(){

    sf::Event event;

    while(this->mainWindow.pollEvent(event)){

      if(event.type == sf::Event::KeyReleased)
        keyboard(event);
      else if(event.type == sf::Event::Resized)
        push=true;
      else
        event_close(event);

    }
  }

  void survival_end_game(){

      if(this->score<=0){
        this->end=true;
        this->menuChoice=1;
        this->game=false;
        this->gameInitialised=false;
      }
  }

  void end_game(){

    switch(this->gameMode){

      case 1:
        if(!this->life){
          this->end=true;
          this->menuChoice=1;
          this->game=false;
          this->gameInitialised=false;
        }
        break;
      case 2:
        if(this->score>5000){
          this->end=true;
          this->menuChoice=1;
          this->game=false;
          this->gameInitialised=false;
        }
        break;
      default:
        cout<<"ERROR end_game"<<endl;
        break;

    }
  }

  void event_close(sf::Event event){
    if(event.type == sf::Event::Closed)
      this->mainWindow.close();
  }

  void display(Board &gameBoard, vector<Bloc> &vectorBloc, int gameInitialised){

    this->mainWindow.clear();

    if(!game){
      if(intro);

      else if(mainMenu)
        display_menu();
      else if(sure)
        display_sure();
      else if(rules)
        display_rules();
      else if(start)
        display_start();
      else if(end)
        display_end_game();

    }
    else if(gameInitialised)
        display_game(gameBoard, vectorBloc);

    display_sprite();

    this->mainWindow.display();

  }

  void display_sprite(){

    if(this->intro){
        mainWindow.draw(this->tamtam.sprite);
      if(this->real){
        mainWindow.draw(this->adilReal.sprite);
        mainWindow.draw(this->thomasReal.sprite);
      }
      else{
        mainWindow.draw(this->adilPixel.sprite);
        mainWindow.draw(this->thomasPixel.sprite);
      }

    }

    else if (mainMenu){
      mainWindow.draw(this->spriteTetris.sprite);
      mainWindow.draw(this->spriteGuide.sprite);
      mainWindow.draw(this->spritePhrase.sprite);
      mainWindow.draw(this->adilPixel.sprite);
      mainWindow.draw(this->thomasPixel.sprite);
    }
    else if(sure){
      mainWindow.draw(this->spriteSure.sprite);
      mainWindow.draw(this->adilPixel.sprite);
      mainWindow.draw(this->thomasPixel.sprite);
    }
    else if(rules){
      mainWindow.draw(this->spriteRules.sprite);
      mainWindow.draw(this->spriteRead.sprite);
      mainWindow.draw(this->spriteBackRules.sprite);
    }
    else if(start){
      mainWindow.draw(this->spriteSettings.sprite);
      mainWindow.draw(this->spritePlus.sprite);
      mainWindow.draw(this->spriteMoins.sprite);
      mainWindow.draw(this->spriteGood.sprite);
      mainWindow.draw(this->adilPixel.sprite);
      mainWindow.draw(this->thomasPixel.sprite);

    }
    else if(game){

      if(!boom){
        mainWindow.draw(this->miniHeadAdil.sprite);
        mainWindow.draw(this->miniHeadThomas.sprite);
      }

      else{
        mainWindow.draw(this->miniHeadAdil2.sprite);
        mainWindow.draw(this->miniHeadThomas2.sprite);
      }
    }
  }

  void keyboard(sf::Event event){

    this->push=true;
    if(event.key.code == sf::Keyboard::Up)
      this->up=true;
    else if(event.key.code == sf::Keyboard::Down)
      this->down=true;
    else if(event.key.code == sf::Keyboard::Left)
      this->left=true;
    else if(event.key.code == sf::Keyboard::Right)
      this->right=true;

    else if(event.key.code == sf::Keyboard::Escape){
      escape=true;
    }
    else if(event.key.code == sf::Keyboard::Space){
      space=true;
    }
  }

////////////////////////////MENU////////////////////////////////////////////////

  void menu(){

    if(mainMenu)
      menu_manage();
    else if(sure)
      sure_manage();
    else if(rules){
      if(this->space){
        this->menuSpace.play();
        this->space=false;
        rules=false;
        mainMenu=true;

      }
    }
    else if(start)
      start_manage();
    else if(this->end)
      end_game_manage();

  }//manage severals menu pages

  void menu_manage(){

    if(this->up){
      if(this->menuChoice==1)
        this->menuChoice=3;
      else
        this->menuChoice--;
      this->menuArrow.play();
      this->up=false;
    }
    else if(this->down){
      if(this->menuChoice==3)
        this->menuChoice=1;
      else
        this->menuChoice++;
      this->menuArrow.play();
      this->down=false;
    }
    else if(this->space){
      this->menuSpace.play();
      switch(this->menuChoice){
        case 1:
          this->mainMenu=false;
          this->start=true;
          break;
        case 2:
          this->mainMenu=false;
          this->rules=true;
          break;
        case 3:
          this->mainMenu=false;
          this->sure=true;
          this->menuChoice=2;
          break;
        default:
          cout<<"ERROR KEYBOARD MAIN MENU"<<endl;
          break;
      }
      this->space=false;
    }
  }//main menu page

  void sure_manage(){

    if(this->left){
      if(this->menuChoice==1)
        this->menuChoice=2;
      else
        this->menuChoice--;
      this->menuArrow.play();
      this->left=false;
    }
    else if(this->right){
      if(this->menuChoice==2)
        this->menuChoice=1;
      else
        this->menuChoice++;
      this->menuArrow.play();
      this->right=false;
    }
    else if(this->space){
      this->menuSpace.play();
      switch(this->menuChoice){
        case 1:
          this->mainWindow.close();
          break;
        case 2:
          this->sure=false;
          this->mainMenu=true;
          this->menuChoice=3;
          break;
        default:
          cout<<"ERROR KEYBOARD SURE"<<endl;
          break;
      }
      this->space=false;
    }
  }//quit menu page

  void start_manage(){

    if(this->up){
      if(this->menuChoice==1)
        this->menuChoice=10;
      else
        this->menuChoice--;
      this->menuArrow.play();
      this->up=false;
    }
    else if(this->down){
      if(this->menuChoice==10)
        this->menuChoice=1;
      else
        this->menuChoice++;
      this->menuArrow.play();
      this->down=false;
    }
    else if(this->left){
      this->menuArrow.play();
      switch(this->menuChoice){

        case 1:
          if(this->boardH>21)
            this->boardH--;
          break;
        case 2:
          if(this->boardW>21)
            this->boardW--;
          break;
        case 3:
          if(this->boardType==1)
            this->boardType=3;
          else
            this->boardType--;
          break;
        case 4:
          if(this->pickType==1)
            this->pickType=2;
          else
            this->pickType--;
          break;
        case 5:
          if(this->blocPossible)
            this->blocPossible=false;
          else
            this->blocPossible=true;
          break;
        case 6:
          if(this->difficultyIncrease)
            this->difficultyIncrease=false;
          else
            this->difficultyIncrease=true;
          break;
        case 8:
          if(this->gameMode==1)
            this->gameMode=3;
          else
            this->gameMode--;
          break;
        case 7:
          if(this->head)
            this->head=false;
          else
            this->head=true;
          break;
        default:
          cout<<"ERROR settings()"<<endl;
          break;
      }
      this->left=false;
    }
    else if(this->right){
      this->menuArrow.play();
      switch(this->menuChoice){

        case 1:
          if(this->boardH<80)
            this->boardH++;
          break;
        case 2:
          if(this->boardW<80)
            this->boardW++;
          break;
        case 3:
          if(this->boardType==3)
            this->boardType=1;
          else
            this->boardType++;
          break;
        case 4:
          if(this->pickType==2)
            this->pickType=1;
          else
            this->pickType++;
          break;
        case 5:
          if(this->blocPossible)
            this->blocPossible=false;
          else
            this->blocPossible=true;
          break;
        case 6:
          if(this->difficultyIncrease)
            this->difficultyIncrease=false;
          else
            this->difficultyIncrease=true;
          break;
        case 8:
          if(this->gameMode==3)
            this->gameMode=1;
          else
            this->gameMode++;
          break;
        case 7:
          if(this->head)
            this->head=false;
          else
            this->head=true;
          break;
        default:
          cout<<"ERROR settings()"<<endl;
          break;
      }
     this->right=false;
    }
    else if(this->space){
      this->menuSpace.play();
      if(this->menuChoice==9){
        this->start=false;
        this->mainMenu=true;
        this->menuChoice=1;
      }
      else if(this->menuChoice==10){
        this->start=false;
        this->game=true;
      }
      this->space=false;
    }
  }//settings menu page

  void display_menu(){

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(35);
    string string;

    sf::RectangleShape start(sf::Vector2f(this->screenW/2, this->screenH/8));
    start.setPosition(this->screenW/4, this->screenH/4);
    start.setOutlineThickness(this->screenH/1000);
    start.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==1)
      start.setFillColor(sf::Color(200, 200, 200));
    else
      start.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(start);

    string="Start";
    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/25, this->screenH/7+this->screenH/200+1.1*(this->screenH/8));
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

    sf::RectangleShape rules(sf::Vector2f(this->screenW/2, this->screenH/8));
    rules.setPosition(this->screenW/4, this->screenH/2);
    rules.setOutlineThickness(this->screenH/1000);
    rules.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==2)
      rules.setFillColor(sf::Color(200, 200, 200));
    else
      rules.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(rules);

    string="Rules";
    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/25, this->screenH/7+this->screenH/200+3.1*(this->screenH/8));
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

    sf::RectangleShape quit(sf::Vector2f(this->screenW/2, this->screenH/8));
    quit.setPosition(this->screenW/4, this->screenH/2+this->screenH/4);
    quit.setOutlineThickness(this->screenH/1000);
    quit.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==3)
      quit.setFillColor(sf::Color(200, 200, 200));
    else
      quit.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(quit);

    string="Exit";
    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/25, this->screenH/7+this->screenH/200+5.1*(this->screenH/8));
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

  }//display main menu page

  void display_sure(){

    sf::Text text,text1;
    text.setFont(font);
    text.setCharacterSize(50);
    text1.setFont(font);
    text1.setCharacterSize(20);
    string string;


    sf::RectangleShape yes(sf::Vector2f(this->screenW/6, this->screenH/6));
    yes.setPosition(this->screenW/4, this->screenH/2);
    yes.setOutlineThickness(this->screenH/1000);
    yes.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==1)
      yes.setFillColor(sf::Color(200, 200, 200));
      else
        yes.setFillColor(sf::Color(60, 60, 60));
      this->mainWindow.draw(yes);

    string="yes";
    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/5, this->screenH/7+this->screenH/200+3*(this->screenH/8));
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

    sf::RectangleShape no(sf::Vector2f(this->screenW/6, this->screenH/6));
    no.setPosition(this->screenW/1.75f, this->screenH/2);
    no.setOutlineThickness(this->screenH/1000);
    no.setOutlineColor(sf::Color(255, 255, 255));

      if(menuChoice==2)
        no.setFillColor(sf::Color(200, 200, 200));
        else
          no.setFillColor(sf::Color(60, 60, 60));
        this->mainWindow.draw(no);

      string="No";
      text.setString(string);
      text.setPosition(this->screenW-this->screenW/2.70, this->screenH/7+this->screenH/200+3.1*(this->screenH/8));
      text.setFillColor(sf::Color(255,0,0));
      string="(back to the menu)";
      text1.setString(string);
      text1.setPosition(this->screenW-this->screenW/2.43, this->screenH/7+this->screenH/200+3.81*(this->screenH/8));
      text1.setFillColor(sf::Color(255,0,0));
      this->mainWindow.draw(text);
      this->mainWindow.draw(text1);


  }//display quit menu page

  void display_rules(){

    sf::Text text,text_rules,text_rules2,text_rules3,text_rules4,text_rules5,text_rules6,text_rules7;
    text.setFont(font);
    text.setCharacterSize(40);
    text_rules.setFont(font);
    text_rules.setCharacterSize(24);
    text_rules2.setFont(font);
    text_rules2.setCharacterSize(24);
    text_rules3.setFont(font);
    text_rules3.setCharacterSize(24);
    text_rules4.setFont(font);
    text_rules4.setCharacterSize(24);
    text_rules5.setFont(font);
    text_rules5.setCharacterSize(24);
    text_rules6.setFont(font);
    text_rules6.setCharacterSize(24);
    text_rules7.setFont(font);
    text_rules7.setCharacterSize(24);
    string string;

      string="- Use the arrows to move,space to select it.";
      text_rules.setString(string);
      text_rules.setPosition(this->screenW/2-this->screenW/3, this->screenH/7+this->screenH/200+1*(this->screenH/8));
      text_rules.setFillColor(sf::Color(255,0,0));

      string="- Press escape to unselect a bloc.";
      text_rules2.setString(string);
      text_rules2.setPosition(this->screenW/2-this->screenW/3, this->screenH/7+this->screenH/200+1.5*(this->screenH/8));
      text_rules2.setFillColor(sf::Color(255,0,0));

      string="- For the differents games mode : ";
      text_rules3.setString(string);
      text_rules3.setPosition(this->screenW/2-this->screenW/3, this->screenH/7+this->screenH/200+2.0*(this->screenH/8));
      text_rules3.setFillColor(sf::Color(255,0,0));

      string="- Normal : 3 placements errors equal at the end of the game.";
      text_rules4.setString(string);
      text_rules4.setPosition(this->screenW/2-this->screenW/3, this->screenH/7+this->screenH/200+2.5*(this->screenH/8));
      text_rules4.setFillColor(sf::Color(255,0,0));

      string="- MaxBefore : place the maximum of bloc possible before 5000 score.";
      text_rules5.setString(string);
      text_rules5.setPosition(this->screenW/2-this->screenW/3, this->screenH/7+this->screenH/200+3.0*(this->screenH/8));
      text_rules5.setFillColor(sf::Color(255,0,0));

      string="- Survial : How many time do you survive before the score reach 0 ?";
      text_rules6.setString(string);
      text_rules6.setPosition(this->screenW/2-this->screenW/3, this->screenH/7+this->screenH/200+3.5*(this->screenH/8));
      text_rules6.setFillColor(sf::Color(255,0,0));




      this->mainWindow.draw(text_rules);
      this->mainWindow.draw(text_rules2);
      this->mainWindow.draw(text_rules3);
      this->mainWindow.draw(text_rules4);
      this->mainWindow.draw(text_rules5);
      this->mainWindow.draw(text_rules6);
      this->mainWindow.draw(text_rules7);




  }//display rules page

  void display_start(){

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    string string;


    sf::RectangleShape height(sf::Vector2f(this->screenW/2, this->screenH/17));
    height.setPosition(this->screenW/4, this->screenH/8);
    height.setOutlineThickness(this->screenH/1000);
    height.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==1)
      height.setFillColor(sf::Color(200, 200, 200));
    else
      height.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(height);

    string=to_string(this->boardH);
    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/80, this->screenH/8+this->screenH/100);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);


    sf::RectangleShape width(sf::Vector2f(this->screenW/2, this->screenH/17));
    width.setPosition(this->screenW/4, this->screenH/8+this->screenH/13);
    width.setOutlineThickness(this->screenH/1000);
    width.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==2)
      width.setFillColor(sf::Color(200, 200, 200));
    else
      width.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(width);

    string=to_string(this->boardW);
    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/80, this->screenH/8+this->screenH/13+this->screenH/100);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);



    sf::RectangleShape board(sf::Vector2f(this->screenW/2, this->screenH/17));
    board.setPosition(this->screenW/4, this->screenH/8+2*(this->screenH/13));
    board.setOutlineThickness(this->screenH/1000);
    board.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==3)
      board.setFillColor(sf::Color(200, 200, 200));
    else
      board.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(board);

    switch(boardType){
      case 1:
        string="Cercle";
        break;
      case 2:
        string="Losange";
        break;
      case 3:
        string="Triangle";
        break;
      default:
        cout<<"ERROR display_settings boardType"<<endl;
        break;
    }

    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/30, this->screenH/8+2*(this->screenH/13)+this->screenH/100);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

    sf::RectangleShape pick(sf::Vector2f(this->screenW/2, this->screenH/17));
    pick.setPosition(this->screenW/4, this->screenH/8+3*(this->screenH/13));
    pick.setOutlineThickness(this->screenH/1000);
    pick.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==4)
      pick.setFillColor(sf::Color(200, 200, 200));
    else
      pick.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(pick);

    switch(pickType){
      case 1:
        string="All blocs";
        break;
      case 2:
        string="3 blocs";
        break;
      default:
        cout<<"ERROR display_settings boardType"<<endl;
        break;
    }

    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/30, this->screenH/8+3*(this->screenH/13)+this->screenH/100);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);


    sf::RectangleShape possible(sf::Vector2f(this->screenW/2, this->screenH/17));
    possible.setPosition(this->screenW/4, this->screenH/8+4*(this->screenH/13));
    possible.setOutlineThickness(this->screenH/1000);
    possible.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==5)
      possible.setFillColor(sf::Color(200, 200, 200));
    else
      possible.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(possible);

    if(this->blocPossible)
      string="Only bloc Possible : Enabled";
    else
      string="Only bloc Possible : Disabled";

    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/10, this->screenH/8+4*(this->screenH/13)+this->screenH/100);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

    sf::RectangleShape difficulty(sf::Vector2f(this->screenW/2, this->screenH/17));
    difficulty.setPosition(this->screenW/4, this->screenH/8+5*(this->screenH/13));
    difficulty.setOutlineThickness(this->screenH/1000);
    difficulty.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==6)
      difficulty.setFillColor(sf::Color(200, 200, 200));
    else
      difficulty.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(difficulty);

    if(this->difficultyIncrease)
      string="Difficulty Increase : Enabled";
    else
      string="Difficulty Increase : Disabled";

    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/10, this->screenH/8+5*(this->screenH/13)+this->screenH/100);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);



    sf::RectangleShape headDanse(sf::Vector2f(this->screenW/2, this->screenH/17));
    headDanse.setPosition(this->screenW/4, this->screenH/8+6*(this->screenH/13));
    headDanse.setOutlineThickness(this->screenH/1000);
    headDanse.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==7)
      headDanse.setFillColor(sf::Color(200, 200, 200));
    else
      headDanse.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(headDanse);

    if(this->head)
      string="Head Dance : Enabled";
    else
      string="Head Dance : Disabled";
    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/15, this->screenH/8+6*(this->screenH/13)+this->screenH/100);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);



    sf::RectangleShape mode(sf::Vector2f(this->screenW/2, this->screenH/17));
    mode.setPosition(this->screenW/4, this->screenH/8+7*(this->screenH/13));
    mode.setOutlineThickness(this->screenH/1000);
    mode.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==8)
      mode.setFillColor(sf::Color(200, 200, 200));
    else
      mode.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(mode);

    switch(this->gameMode){

      case 1:
        string="Game mode : Normal";
        break;
      case 2:
        string="Game mode : MaxBefore";
        break;
      case 3:
        string="Game mode : Survival";
        break;
      default:
        cout<<"ERROR start_display -> GAMEMODE"<<endl;
        break;
    }

    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/15, this->screenH/8+7*(this->screenH/13)+this->screenH/100);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);


    sf::RectangleShape back(sf::Vector2f(this->screenW/2, this->screenH/17));
    back.setPosition(this->screenW/4, this->screenH/8+8*(this->screenH/13));
    back.setOutlineThickness(this->screenH/1000);
    back.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==9)
      back.setFillColor(sf::Color(200, 200, 200));
    else
      back.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(back);

    string="Back";
    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/30, this->screenH/8+8*(this->screenH/13)+this->screenH/100);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);



    sf::RectangleShape start(sf::Vector2f(this->screenW/2, this->screenH/17));
    start.setPosition(this->screenW/4, this->screenH/8+9*(this->screenH/13));
    start.setOutlineThickness(this->screenH/1000);
    start.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==10)
      start.setFillColor(sf::Color(200, 200, 200));
    else
      start.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(start);

    string="Start";
    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/30, this->screenH/8+9*(this->screenH/13)+this->screenH/100);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

  }//display settings menu page

  void end_game_manage(){

    if(this->up){
      if(this->menuChoice==1)
        this->menuChoice=2;
      else
        this->menuChoice--;
      this->menuArrow.play();
      this->up=false;
    }

    if(this->down){
      if(this->menuChoice==1)
        this->menuChoice=2;
      else
        this->menuChoice--;
      this->menuArrow.play();
      this->down=false;
    }

    else if(this->space){
      this->menuSpace.play();
      switch(this->menuChoice){
        case 1:
          this->head=false;
          this->blocNumber=0;
          this->piece=0;
          this->score=0;
          this->life=3;
          this->mainMenu=true;
          this->end=false;
          this->boardH=50;
          this->boardW=50;
          this->boardType=1;
          this->pickType=1;
          this->blocPossible=false;
          this->difficultyIncrease=false;
          this->gameMode=1;
          this->gameInitialised=false;
          this->minute=0;
          this->seconde=0;
          this->scorePerSec=2;
          break;
        case 2:
          this->mainWindow.close();
          break;
        default:
          cout<<"ERROR KEYBOARD MAIN MENU"<<endl;
          break;
      }
      this->space=false;
    }


  }

  void display_end_game(){

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(70);
    string string;
    text.setFillColor(sf::Color(0,255,0));

    string="FIN DE PARTIE";
    text.setString(string);
    text.setPosition(this->screenW/3-this->screenW/40, this->screenH/14);
    this->mainWindow.draw(text);

    text.setCharacterSize(50);
    text.setFillColor(sf::Color(255,0,0));
    switch(this->gameMode){

      case 1:
        string="SCORE FINAL :";
        text.setString(string);
        text.setPosition(this->screenW/4, this->screenH/4);
        this->mainWindow.draw(text);
        string=to_string(this->score);
        text.setString(string);
        text.setPosition(this->screenW/2+this->screenW/6, this->screenH/4);
        this->mainWindow.draw(text);
        break;
      case 2:
        string="NOMBRE DE BLOCS :";
        text.setString(string);
        text.setPosition(this->screenW/4, this->screenH/4);
        this->mainWindow.draw(text);
        string=to_string(this->blocNumber);
        text.setString(string);
        text.setPosition(this->screenW/2+this->screenW/6, this->screenH/4);
        this->mainWindow.draw(text);
        break;
      case 3:
        string="TEMPS SURVECU :";
        text.setString(string);
        text.setPosition(this->screenW/4, this->screenH/4);
        this->mainWindow.draw(text);
        string=to_string(this->minute);
        text.setString(string);
        text.setPosition(this->screenW/2+this->screenW/6, this->screenH/4);
        this->mainWindow.draw(text);
        string="min";
        text.setString(string);
        text.setPosition(this->screenW/2+this->screenW/6+this->screenW/20, this->screenH/4);
        this->mainWindow.draw(text);
        string=to_string(this->seconde);
        text.setString(string);
        text.setPosition(this->screenW/2+this->screenW/6+this->screenW/7, this->screenH/4);
        this->mainWindow.draw(text);
        string="s";
        text.setString(string);
        text.setPosition(this->screenW/2+this->screenW/6+this->screenW/5, this->screenH/4);
        this->mainWindow.draw(text);

        break;
    }

    text.setCharacterSize(40);
    sf::RectangleShape menu(sf::Vector2f(this->screenW/2, this->screenH/8));
    menu.setPosition(this->screenW/4, this->screenH/2);
    menu.setOutlineThickness(this->screenH/1000);
    menu.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==1)
      menu.setFillColor(sf::Color(200, 200, 200));
    else
      menu.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(menu);

    string="MAIN MENU";
    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/12, this->screenH/2+this->screenH/40);
    this->mainWindow.draw(text);

    sf::RectangleShape quit(sf::Vector2f(this->screenW/2, this->screenH/8));
    quit.setPosition(this->screenW/4, this->screenH/2+this->screenH/4);
    quit.setOutlineThickness(this->screenH/1000);
    quit.setOutlineColor(sf::Color(255, 255, 255));

    if(menuChoice==2)
      quit.setFillColor(sf::Color(200, 200, 200));
    else
      quit.setFillColor(sf::Color(60, 60, 60));
    this->mainWindow.draw(quit);

    string="QUIT";
    text.setString(string);
    text.setPosition(this->screenW/2-this->screenW/30, this->screenH/2+this->screenH/4+this->screenH/40);
    this->mainWindow.draw(text);

  }

/////////////////////////////GAME///////////////////////////////////////////////

void manage_game(vector<Bloc> &vectorBloc, Board &gameBoard){

  if(this->selectedPiece)
    manage_gameBoard(gameBoard);

  else
    manage_gameBloc(vectorBloc);
}

void manage_gameBoard(Board &gameBoard){

  if(this->up){
    this->moveBoard.play();
    if(this->selectedY==0)
      this->selectedY=this->boardH-1;
    else
      this->selectedY--;

    if(gameBoard.board[selectedY][selectedX]==-1){
      this->selectedY=this->boardH-1;
      while(gameBoard.board[selectedY][selectedX]==-1){
        this->selectedY--;
      }
    }
    this->up=false;
  }
  if(this->down){
    this->moveBoard.play();
    if(this->selectedY==this->boardH-1)
      this->selectedY=0;
    else
      this->selectedY++;

    if(gameBoard.board[selectedY][selectedX]==-1){
      this->selectedY=0;
      while(gameBoard.board[selectedY][selectedX]==-1){
        this->selectedY++;
      }
    }
    this->down=false;
  }
  if(this->left){
    this->moveBoard.play();
    if(this->selectedX==0)
      this->selectedX=this->boardW-1;
    else
      this->selectedX--;

    if(gameBoard.board[selectedY][selectedX]==-1){
      this->selectedX=this->boardW-1;
      while(gameBoard.board[selectedY][selectedX]==-1){
        this->selectedX--;
      }
    }
    this->left=false;
  }
  if(this->right){
    this->moveBoard.play();
    if(this->selectedX==this->boardW-1)
      this->selectedX=0;
    else
      this->selectedX++;
    if(gameBoard.board[selectedY][selectedX]==-1){
      this->selectedX=0;
      while(gameBoard.board[selectedY][selectedX]==-1){
        this->selectedX++;
      }
    }
    this->right=false;
  }
  if(this->space){
    this->place=true;
    this->space=false;
  }
  if(this->escape){
    this->menuArrow.play();
    this->selectedPiece=false;
    this->escape=false;
  }
}

void manage_gameBloc(vector <Bloc> &vectorBloc){

  if(this->up){
    if(this->piece>2){
      this->changeBloc.play();
      this->piece-=3;
    }
    this->up=false;
  }
  if(this->down){
    if(this->piece<vectorBloc.size()-3){
      this->changeBloc.play();
      this->piece+=3;
    }
    this->down=false;
  }
  if(this->left){
    if(this->piece%3!=0){
      this->changeBloc.play();
      this->piece--;
    }
    this->left=false;
  }
  if(this->right){
    if(this->piece%3!=2 && this->piece!=vectorBloc.size()-1){
      this->changeBloc.play();
      this->piece++;
    }
    this->right=false;
  }
  if(this->space){
    this->menuArrow.play();
    this->selectedPiece=true;
    this->space=false;
  }
  if(this->escape){
    this->escape=false;
  }//pause ou quitter à définir

}

void display_game(Board &gameBoard, vector<Bloc> &vectorBloc){

  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(24);
  string string;
  int x, y, height, width;

  string="SCORE :";
  text.setString(string);
  text.setPosition(this->screenW/8, this->screenH/30);
  text.setFillColor(sf::Color(255,0,0));
  this->mainWindow.draw(text);

  string=to_string(this->score);
  text.setString(string);
  text.setPosition(this->screenW/4, this->screenH/30);
  text.setFillColor(sf::Color(255,0,0));
  this->mainWindow.draw(text);

  if(this->gameMode==1){

    string="LIFE :";
    text.setString(string);
    text.setPosition(this->screenW/2, this->screenH/30);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

    string=to_string(this->life);
    text.setString(string);
    text.setPosition(this->screenW/2+this->screenW/16, this->screenH/30);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

  }

  if(this->gameMode==2){

    string="BLOC :";
    text.setString(string);
    text.setPosition(this->screenW/2, this->screenH/30);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

    string=to_string(this->blocNumber);
    text.setString(string);
    text.setPosition(this->screenW/2+this->screenW/16, this->screenH/30);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);


  }

  if(this->gameMode==3){

    string="TIME :";
    text.setString(string);
    text.setPosition(this->screenW/2, this->screenH/30);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

    string=to_string(this->minute);
    text.setString(string);
    text.setPosition(this->screenW/2+this->screenW/16, this->screenH/30);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

    string="min";
    text.setString(string);
    text.setPosition(this->screenW/2+this->screenW/16+this->screenW/40, this->screenH/30);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

    string=to_string(this->seconde);
    text.setString(string);
    text.setPosition(this->screenW/2+this->screenW/16+3*this->screenW/40, this->screenH/30);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

    string="s";
    text.setString(string);
    text.setPosition(this->screenW/2+this->screenW/16+4*this->screenW/40, this->screenH/30);
    text.setFillColor(sf::Color(255,0,0));
    this->mainWindow.draw(text);

  }

  height=this->screenH/2+this->screenH/3;
  width=this->screenW/2+this->screenW/6;
  x=this->screenW/30;

  switch(gameBoard.boardType){
    case 1: case 2:
      y=this->screenH/10;
      break;
    case 3:
      y=this->screenH/4+this->screenH/10;
      break;
    default:
      break;
  }
  display_board(gameBoard, x, y, height, width);

  y=this->screenH/10;
  x=this->screenW/2+this->screenW/5+this->screenW/30;
  width=this->screenW/4;
  display_vectorBloc(vectorBloc, x, y, width);
}

void display_board(Board &gameBoard, int x, int y, int height, int width){

  int boardW, boardH;
  int i, j, xCopy;

  if(this->boardW>this->boardH)
    boardW=boardH=this->boardW;
  else
    boardH=boardW=this->boardH;

  if(gameBoard.boardType==1){
    if(this->boardW>this->boardH)
      y+=((this->boardW-this->boardH)/2)*(height/boardH);
    else
      x+=((this->boardH-this->boardW)/2)*(width/boardW);
  }

  xCopy=x;
  sf::RectangleShape cases(sf::Vector2f(width/boardW, height/boardH));


  for(j=0; j<this->boardH; j++){
    for(i=0; i<this->boardW; i++){
      cases.setPosition(x, y);
      cases.setOutlineColor(sf::Color(255, 255, 255));
      x+=width/boardW;

      if(j==this->selectedY && i==this->selectedX && this->selectedPiece){
        cases.setOutlineThickness(this->screenH/500);
        cases.setFillColor(sf::Color(20, 20, 20));
      }

      else{
        cases.setOutlineThickness(this->screenH/1000);
        if(gameBoard.board[j][i]==0)
          cases.setFillColor(sf::Color(200, 200, 200));
        else if(gameBoard.board[j][i]>0)
          color_case(cases, gameBoard.board[j][i]);
      }
      if(gameBoard.board[j][i]>-1)
        this->mainWindow.draw(cases);

    }
    x=xCopy;
    y+=height/boardH;
  }
}

void display_vectorBloc(vector<Bloc> &vectorBloc, int x, int y, int width){

  uint caseSize, xSave, i;
  xSave=x;
  caseSize=width/17;

  if(this->piece/3>4)
    y-=(caseSize*7)*(this->piece/3-4);

  for(i=0; i<vectorBloc.size(); i++){
    if(i!=0 && i%3==0){
      x=xSave;
      y+=caseSize*7;
    }

    if(i==this->piece)
      display_bloc(vectorBloc[i], x, y, caseSize, 1);
    else
      display_bloc(vectorBloc[i], x, y, caseSize, 0);

    x+=caseSize*7;
  }

}

void display_bloc(Bloc &bloc, int x, int y, int caseSize, int selected){

  sf::RectangleShape cases(sf::Vector2f(caseSize, caseSize));
  int i, j, xCopy;
  xCopy=x;

  for(j=0; j<bloc.height; j++){
    for(i=0; i<bloc.width; i++){

      cases.setPosition(x, y);
      cases.setOutlineColor(sf::Color(255, 255, 255));

      if(selected){
        cases.setOutlineThickness(this->screenH/500);

        if(i==bloc.i && j==bloc.height-1 && bloc.number!=0)
          cases.setFillColor(sf::Color(200, 200, 200));
        else
          cases.setFillColor(sf::Color(20, 20, 20));
      }
      else{
        cases.setOutlineThickness(this->screenH/1000);
        if(i==bloc.i && j==bloc.height-1)
          cases.setFillColor(sf::Color(200, 200, 200));
        else
          color_case(cases, bloc.bloc[j][i]);

      }

      if(bloc.bloc[j][i]!=0)
        this->mainWindow.draw(cases);
      x+=caseSize;
    }
    y+=caseSize;
    x=xCopy;
  }
}

void color_case(sf::RectangleShape &cases, int color){

  switch(color){

    case 0 ://black
      cases.setFillColor(sf::Color(0,0,0));
      break;
    case 1 ://white
      cases.setFillColor(sf::Color(255,255,255));
      break;
    case 2 ://blue
      cases.setFillColor(sf::Color(0,0,255));
      break;
    case 3 ://magenta
      cases.setFillColor(sf::Color(255,0,255));
      break;
    case 4 ://cyan
      cases.setFillColor(sf::Color(0,255,255));
      break;
    case 5 ://green
      cases.setFillColor(sf::Color(0,255,0));
      break;
    case 6 ://orange
      cases.setFillColor(sf::Color(255,165,0));
      break;
    case 7 ://red
      cases.setFillColor(sf::Color(255,0,0));
      break;
    case 8 ://yellow
      cases.setFillColor(sf::Color(255,255,0));
      break;

  }
}


};
