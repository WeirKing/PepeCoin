#include		<SFML/Graphics.hpp>
#include		<time.h>

using namespace sf;

int main(){
	RenderWindow window(VideoMode(380,480), "My gayme");

	while (window.isOpen()){
		Event e;
		while(window.pollEvent(e)){
			if (e.type == Event::Closed){
				window.close();
			}
		}
	}
}