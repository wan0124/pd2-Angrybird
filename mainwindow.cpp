#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);

    count=0;
    chance=4;
    enemy=3;
    wait=0;
    score=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    world->SetContactListener(new boom());
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    // Create ground (You can edit here)
    Shot = new shot(150,650,QPixmap(":/image/shot.png").scaled(75,150),world,scene);
    land = new Land(16.0,1.0,16.0,1.0,QPixmap(":/ground.png").scaled(width(),height()*2/18),world,scene);
    GameSet();

    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(next_bird()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(dead()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(Wait()));
    timer.start(100/6);
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    if(chance>count)
    {
        if(event->type() == QEvent::MouseButtonPress && wait>0)
        {
            QMouseEvent *keyEvent = static_cast<QMouseEvent *>(event);
            if(Bird_List[count]->fire)
            {
                Bird_List[count]->Special();
            }

            if(Bird_List[count]->shoot)
                if((190-50)<keyEvent->x() && keyEvent->x()<(190+50))
                    if((675-50)<keyEvent->y() && keyEvent->y()<(675+50))
                    {
                        start.setX(keyEvent->x());
                        start.setY(keyEvent->y());
                        Bird_List[count]->ready = true;
                    }
            wait=0;
        }

        if(event->type() == QEvent::MouseMove)
        {
            QMouseEvent *keyEvent = static_cast<QMouseEvent *>(event);
            if(Bird_List[count]->ready && !Bird_List[count]->fire )
            {
                float x=3.8-((start.x()-keyEvent->x())/50.0);
                float y=4.5+((start.y()-keyEvent->y())/50.0);
                Bird_List[count]->g_body->SetTransform(b2Vec2(x,y),0);
            }
        }
        if(event->type() == QEvent::MouseButtonRelease && wait>0)
        {
            QMouseEvent *keyEvent = static_cast<QMouseEvent *>(event);
            if(Bird_List[count]->ready && !Bird_List[count]->fire )
            {
                end.setX(keyEvent->x());
                end.setY(keyEvent->y());

                Bird_List[count]->g_body->SetType(b2_dynamicBody);
                Bird_List[count]->setLinearVelocity(b2Vec2((start.x()-end.x())/7.5,-(start.y()-end.y())/7.5));
                Bird_List[count]->fire = true;

                wait=0;

            }
            wait=0;
        }
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::GameSet()
{
    ui->complete->hide();
    ui->fail->hide();

    wall *wall1 = new wall(world);
    wall1->create(19,4,0.35,1.5,&timer,QPixmap(":/image/wall2.png").scaled(1*22,3*50),world,scene);
    Wall_List.push_back(wall1);

    wall *wall2 = new wall(world);
    wall2->create(22.25,4,0.35,1.5,&timer,QPixmap(":/image/wall2.png").scaled(1*22,3*50),world,scene);
    Wall_List.push_back(wall2);

    wall *wall3 = new wall(world);
    wall3->create(20.5,6,1.75,0.25,&timer,QPixmap(":/image/wall1.png").scaled(3.5*50,0.5*50),world,scene);
    Wall_List.push_back(wall3);

    Bird *bird_1 = new Bird(5.0f,5.0f,0.5f,&timer,QPixmap(":/bird.png").scaled(1*50,1*50),world,scene);
    Shot->ready(bird_1);
    Bird_List.push_back(bird_1);

    yellowbird *bird_2 = new yellowbird(6.0f,5.0f,0.5f,&timer,QPixmap(":/image/YellowBird.png").scaled(1*50,1*50),world,scene);
    Bird_List.push_back(bird_2);

    rockbird *bird_3 = new rockbird(7.0f,5.0f,0.5f,&timer,QPixmap(":/image/rockbird.png").scaled(1*50,1*50),world,scene);
    Bird_List.push_back(bird_3);\

    backbird *bird_4 = new backbird(8.0f,5.0f,0.5f,&timer,QPixmap(":/image/GreenBird.png").scaled(1*50,1*50),world,scene);
    Bird_List.push_back(bird_4);

    Pig *pig1 = new Pig(20,6.5,0.75,&timer,QPixmap(":/image/pig.png").scaled(1.5*50,1.5*50),world,scene);
    Pig_List.push_back(pig1);

    Pig *pig2 = new Pig(20,4.5,0.75,&timer,QPixmap(":/image/pig.png").scaled(1.5*50,1.5*50),world,scene);
    Pig_List.push_back(pig2);

    Pig *pig3 = new Pig(23,4.5,0.75,&timer,QPixmap(":/image/pig.png").scaled(1.5*50,1.5*50),world,scene);
    Pig_List.push_back(pig3);
}

void MainWindow::next_bird()
{
    if(Bird_List[count]->g_body->GetLinearVelocity().Length()<0.1 || wait>500)
    {
        if(Bird_List[count]->fire && chance-1 > count)
        {
            delete Bird_List[count];
            Bird_List[count]=NULL;
            count++;
            Shot->ready(Bird_List[count]);
        }
    }
    if(Bird_List[chance-1]->g_body->GetLinearVelocity().Length()<0.01 || wait>500)
    {
        if(count==3 && Bird_List[count]->fire && enemy>0)
        {
            timer.stop();
            ui->fail->show();
        }
        else if(count==3 && Bird_List[count]->fire && enemy==0)
        {
            timer.stop();
            ui->complete->show();
        }
    }
}

void MainWindow::dead()
{
    int i;
    for(i=0;i<Wall_List.size();i++)
    {
        if(Wall_List[i]!=NULL && Wall_List[i]->dead)
        {
            delete Wall_List[i];
            Wall_List[i]=NULL;

        }
    }

    for(i=0;i<Pig_List.size();i++)
    {
        if(Pig_List[i]!=NULL && Pig_List[i]->dead)
        {
            delete Pig_List[i];
            Pig_List[i]=NULL;
            enemy--;
            score=score+10;
            ui->lcdNumber->display(score);

        }
    }
}

void MainWindow::Wait()
{
    wait++;
}

void MainWindow::on_reStart_clicked()
{
    ui->lcdNumber->display(0);
    timer.stop();
    wait = 0;
    count = 0;
    chance = 3;
    score = 0;
    enemy = 3;

    for(int i=0;i<Wall_List.size();i++)
    {
        if(Wall_List[i]!=NULL)
        {
            delete Wall_List[i];
            Wall_List[i]=NULL;
        }
    }
    for(int i=0;i<Pig_List.size();i++)
    {
        if(Pig_List[i]!=NULL)
        {
            delete Pig_List[i];
            Pig_List[i]=NULL;
        }
    }
    for(int i=0;i<Bird_List.size();i++)
    {
        if(Bird_List[i]!=NULL)
        {
            delete Bird_List[i];
            Bird_List[i]=NULL;
        }
    }
    Wall_List.clear();
    Pig_List.clear();
    Bird_List.clear();

    GameSet();
    timer.start(100/6);
}

void MainWindow::on_Quit_clicked()
{
    emit quitGame();
    exit(0);
}
