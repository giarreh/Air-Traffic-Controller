// Assume Radius = 161 km = 250 pixels
// Assume Danger Zone = 1.5 km
// Assume 1 knot = 1.85 km/h
// Assume only 100 airplanes can be in the area at a time
// Assume 1 time step = 10 seconds

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <random>
#include <chrono>

#include "priorityqueue.h"

#define R 250 // Pixels; Surveillance radius
#define DELAY 100 // Milliseconds; Delay between movements
#define ARRIVAL_RATE 50 // Movements between each arrival
#define CHANGE_RATE 50 // Movements between each change

double pixels = 0.514444 * 0.001 * 0.644 * 10; // (knots / m/s) * (m / km) * (km / pixels) * time step)
double surveillance_r = 500 * 0.1524 * 0.644 ;// feet * (feet / km) * (km / pixels)

using namespace std;
using namespace std::chrono;

struct Flight {
    double x = -10;
    double y = -10;
    int v = 1; // Knots; Velocity
    double a; // radians
    double p; // priority
};

double square(double x);
void move_flight(Node *p);
int to_exit(Node *p);
double random_normal(double mean, double stddev);
Flight new_flight();
void change_flight(Node *p);
void collision_detection(List flights, sf::Clock *clock, sf::Clock *clock2);


int main() {
    int a = ARRIVAL_RATE; // Movement cycles since last arrival
    int c = CHANGE_RATE / 4; // Movment cycles since last change

    sf::Clock clock;
    sf::Clock clock2;

    sf::Time elapsed = clock.getElapsedTime();
    sf::Time elapsed2 = clock2.getElapsedTime();

    Flight f; // Temporary flight

    // Create list
    List flights;
    List tempList;

    flights = CreateList(0);
    tempList = CreateList(0);

    MakeEmptyList(flights);
    MakeEmptyList(tempList);

    //Graphical elements
    sf::RenderWindow window(sf::VideoMode(R * 2, R * 2), "Radar");
    sf::CircleShape outline(R, 255);
    sf::CircleShape plane[100];
    for (int i; i < 100; i++) {
        plane[i].setRadius(5);
        plane[i].setFillColor(sf::Color::Green);
    }

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (a == ARRIVAL_RATE && !Is_100(flights)) {
            f = new_flight();
            InsertList(flights, f.x, f.y, f.v, f.a, f.p);
            a = 0;
        }
        a++;

        Short_queue(flights, tempList);

        struct Node *p;
        p = flights->head->next;
        int i = 1;

        while (p != NULL) {
            if (c == CHANGE_RATE) {
                change_flight(p);
                c = 0;
            }
            c++;

            move_flight(p);

            collision_detection(flights, &clock, &clock2);

            p->priority = to_exit(p);

            if (square(p->x - R) + square(p->y - R) > square(R)) {
                DeleteList(flights);
            } else {
                plane[i].setPosition((float) p->x, (float) p->y);
                window.draw(plane[i]);
            }

            p = p->next;
            i++;
        }

        window.display();
        window.clear();
        window.draw(outline);
        sf::sleep(sf::milliseconds(DELAY));
    }
}

double square(double x){
    return x * x;
}

void move_flight(Node *p) {
    // Angle * (Knots * (knots / m/s) * (m / km) * (km / pixels) * time step)
    p->x += cos(p->rad * M_PI) * (p->speed * pixels);
    p->y += sin(p->rad * M_PI) * (p->speed * pixels);
}

void change_flight(Node *p) {
    int velocity = (int) random_normal(0, 33.4 * 4);

    if (p->speed + velocity >= 200 && p->speed + velocity <= 1000)
        p->speed += velocity;
    else
        p->speed -= velocity;

    p->rad += random_normal(0, 0.25084 / 2);
}

int to_exit(Node *p) {
    int i = 0;
    double x = p->x;
    double y = p->y;

    while (square(x - R) + square(y - R) <= square(R)) {
        x += cos(p->rad * M_PI) * (p->speed * pixels);
        y += sin(p->rad * M_PI) * (p->speed * pixels);
        i++;
    }

    return i;
}

double random_normal(double mean, double stddev) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(mean, stddev);

    return distribution(generator);
}

Flight new_flight() {
    Flight f;

    float r = (float) rand() / (float) (RAND_MAX) * 2;
    f.x = R + R * cos(r * M_PI);
    f.y = R + R * sin(r * M_PI);
    f.a = r + 1;

    while ((f.x - R) * (f.x - R) + (f.y - R) * (f.y - R) > R * R) {
        f.x += cos(f.a * M_PI) * (f.v * 0.514444 * 0.001 * 0.644 * 10);
        f.y += sin(f.a * M_PI) * (f.v * 0.514444 * 0.001 * 0.644 * 10);
    }

    f.v = (int) random_normal(600, 180);

    f.p = f.v / (R * 2 * 0.514444 * 0.001 * 0.644 * 10);

    return f;
}

void collision_detection(List flights, sf::Clock *clock, sf::Clock *clock2){
    int distancetemp;
    int mindistance =1000;
    int x1 = 1000, y1 = 1000, x2 = 1000, y2 = 1000;

    struct Node *w;
    w = flights->head->next;
    while(w != NULL){
        struct Node *q;
        q = flights->head->next;

        while(q != NULL){
            if(!(w->x == q->x && w->y == q->y)) {
                float distance = sqrt((w->x - q->x) * (w->x - q->x) + (w->y - q->y) * (w->y - q->y));
                distancetemp = distance;
                if(mindistance > distancetemp){
                    if(w->x >= 0 && w->y >= 0 && q->x >= 0 && q->y >= 0 ) {
                        if (w->x <= 500 && w->y <= 500 && q->x <= 500 && q->y <= 500) {
                            x1 = w->x;
                            y1 = w->y;
                            x2 = q->x;
                            y2 = q->y;
                        }
                    }
                }
                if (distance <= surveillance_r) {
                    if(clock2->getElapsedTime().asSeconds() > 0.25){
                        printf("Alarm!\n");
                        clock2->restart();
                    }

                    break;
                }

            }
            q = q->next;
        }
        w = w->next;
    }

    if(clock->getElapsedTime().asSeconds() > 1 && x1 != 1000){
        printf("(%d, %d) and (%d, %d) \n", x1, y1, x2, y2);
        clock->restart();
    }

}