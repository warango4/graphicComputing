#include "ofApp.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    game_state = "start";
    score = 0;
    scaleB = false;
    
    max_enemy_amplitude = 3.0;
    max_enemy_shoot_interval = 3;
    
    player_image.load("images/player.png");
    
    player_bullet_sound.load("sounds/player_bullet.mp3");
    
    player_start.set(256, 650);

    float width = 50;
    float height = 50;

    player_1.setup(width, height, player_start);
    
    start_screen.load("images/startScreen.png");
    end_screen.load("images/end_screen.png");
    score_font.load("fonts/steelworks_vintage.otf", 48);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if (game_state == "start") {
        
    } else if (game_state == "game") {
        player_1.update();
        limitPlayer(&player_1.pos);
        update_bullets();
        
        for (int i = 0; i < enemies.size(); i+=1) {
            enemies[i].update();
            if (enemies[i].time_to_shoot()) {
                Bullet b;
                b.setup(false, enemies[i].pos, enemies[i].speed);
                bullets.push_back(b);
            }
        }
        
        if (level_controller.should_spawn() == true) {
            Enemy e;
            e.setup(max_enemy_amplitude, max_enemy_shoot_interval);
            enemies.push_back(e);
        }
    } else if (game_state == "end") {
        
    }
               
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (game_state == "start") {
        start_screen.draw(0,0);
    } else if (game_state == "game") {
        ofBackground(0, 0, 0);
        for (int i = 0; i < enemies.size(); ++i) {
            enemies[i].draw();
        }
        for(int i = 0; i< bullets.size(); ++i) {
            bullets[i].draw();
        }
        
        player_1.draw();
        
        draw_score();
        draw_lives();
    } else if (game_state == "end") {
        end_screen.draw(0,0);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (game_state == "game") {
        if (key == OF_KEY_LEFT)
            player_1.is_left_pressed = true;
        if (key == OF_KEY_RIGHT)
            player_1.is_right_pressed = true;
        if (key == OF_KEY_UP)
            player_1.is_up_pressed = true;
        if (key == OF_KEY_DOWN)
            player_1.is_down_pressed = true;
        if (key == ' ') {
            int despl = 30;
            if(scaleB){
                for(int i = 1; i <= 3; ++i){
                    Bullet b;
                    ofPoint point;
                    if(i == 1){
                        point.x = player_1.pos.x + (despl * -1);
                    } else if (i == 3){
                        point.x = player_1.pos.x + despl;
                    } else {
                        point.x = player_1.pos.x;   
                    }
                    point.y = player_1.pos.y;
                    b.setup(true, point, player_1.speed);
                    bullets.push_back(b);
                }
            } else {
                Bullet b;
                b.setup(true, player_1.pos, player_1.speed);
                bullets.push_back(b);
            }

            player_bullet_sound.play();            
        }
		if (key == 'b') {
            scaleB = true;
            player_1.bigger = true;
        }
        if (key == 's') player_1.smaller = true;

		if (key == 'q') {
			player_1.rotate = true;
            ++player_1.nRotation;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (game_state == "start" && key == ' ') {
        game_state = "game";
        level_controller.setup(ofGetElapsedTimeMillis());
    } else if (game_state == "game") {
        if (key == OF_KEY_LEFT)
            player_1.is_left_pressed = false;
        if (key == OF_KEY_RIGHT)
            player_1.is_right_pressed = false;
        if (key == OF_KEY_UP)
            player_1.is_up_pressed = false;
        if (key == OF_KEY_DOWN)
            player_1.is_down_pressed = false;
		if (key == 'b') {
			player_1.bigger = false;
            scaleB = false; 
        }
		if (key == 's')
            player_1.smaller = false;
        if(key == 'q') player_1.rotate = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::update_bullets() {
    for (int i = 0; i < bullets.size(); i+=1) {
        bullets[i].update();
        if (bullets[i].pos.y - bullets[i].width/2 < 0 || bullets[i].pos.y + bullets[i].width/2 > ofGetHeight()) {
            bullets.erase(bullets.begin() + i);
        }
    }
    check_bullet_collisions();
}

void ofApp::limitPlayer(ofPoint * point) {
    
    if (0 > point->x) {
        point->x = 0;
    }
    if (point->x > ofGetWindowWidth()) {
        point->x = ofGetWindowWidth();
    }
    if (0 > point->y) {
        point->y = 0;
    }
    if(point->y > ofGetWindowHeight()) {
        point->y = ofGetWindowHeight();
    }
}

void ofApp::check_bullet_collisions() {
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i].from_player) {
            for (int e = enemies.size()-1; e >= 0; e--) {
                if (ofDist(bullets[i].pos.x, bullets[i].pos.y, enemies[e].pos.x, enemies[e].pos.y) < (enemies[e].width + bullets[i].width)/2) {
                    enemies.erase(enemies.begin()+e);
                    bullets.erase(bullets.begin()+i);
                    score+=10;
                }
            }
        } else {
            if (ofDist(bullets[i].pos.x, bullets[i].pos.y, player_1.pos.x, player_1.pos.y) < (bullets[i].width+player_1.width)/2) {
                bullets.erase(bullets.begin()+i);
                player_1.lives--;
                
                if (player_1.lives <= 0) {
                    game_state = "end";
                }
            }
        }
    }
}

void ofApp::draw_lives() {
    ofPath path;
    path.setColor(ofColor::red);
    ofFill();
    for (int i = 0; i < player_1.lives; i++) {
        path.circle(ofGetWidth() - (i * player_image.getWidth()) - 100, 30, 15);
        path.draw();
    }
}

void ofApp::draw_score() {
    if (game_state == "game") {
        score_font.drawString(ofToString(score), 30, 72);
    } else if (game_state == "end") {
        float w = score_font.stringWidth(ofToString(score));
        score_font.drawString(ofToString(score), ofGetWidth()/2 - w/2, ofGetHeight()/2 + 100);
    }
}

void ofApp::reset_game() {
    
}
