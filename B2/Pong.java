/**
* Pong.java
* @author 22266055 Shigemura Kazuma
*/

import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class Pong extends JPanel implements Runnable, KeyListener{
    static final int WORLD_W = 320; //画面の横幅
    static final int WORLD_H = 240; //画面の縦幅
    static final int BALL_R = 10; //ボールの半径
    static final int paddle_W = 5; //パドルの横幅
    static final int paddle_H = 50; //パドルの縦幅
    static final int paddle_x = 300; //パドルの初期位置
    private int paddle_y = 150; //パドルの初期位置
    static final double dT = 0.01; //刻み時間
    private int x = WORLD_W/2, y = WORLD_H/2; //ボールの位置
    private double dx = 100.0; //ボールの速度
    private double dy = 100.0; //ボールの速度
    private boolean isRunning = true; //マウスクリックの度に論理フラグが反転

    public Pong(){
        setOpaque(false);
        setPreferredSize(new Dimension(WORLD_W, WORLD_H));
        addKeyListener(this);
        setFocusable(true);
    }
    
    public void run(){
        while(true){
            if(isRunning){
                if(x < BALL_R)dx *= -1.0;
                if(x > WORLD_W-BALL_R)isRunning ^= true;
                if(y < BALL_R || y > WORLD_H-BALL_R)dy *= -1.0;
                if(((x+BALL_R >= paddle_x) && (x+BALL_R < paddle_x+paddle_W)) && ((paddle_y <= y) && (y <= paddle_y+paddle_H)))dx *= -1.0;
                x += dx*dT;
                y += dy*dT;
            }
            repaint();
            try{
                Thread.sleep((int)(dT*1000));
            }
            catch(InterruptedException e){}
        }
    }

    public void paintComponent(Graphics g){
        super.paintComponent(g);
        g.setColor(Color.yellow);
        g.fillOval(x-BALL_R, y-BALL_R, BALL_R*2, BALL_R*2);
        g.setColor(Color.white);
        g.fillRect(paddle_x, paddle_y, paddle_W, paddle_H);
        if(!isRunning){
            try{
                Thread.sleep(1000);
            }
            catch(InterruptedException e){}
            paddle_y = 150; x = WORLD_W/2; y = WORLD_H/2;
            dx = 100.0; dy = 100.0; isRunning = true;
        }
    }

    public void keyTyped(KeyEvent e){}
    public void keyPressed(KeyEvent e){
        switch(e.getKeyCode()){
            case KeyEvent.VK_UP:
            if(paddle_y >= 0)paddle_y = paddle_y - 10;
			break;
		case KeyEvent.VK_DOWN:
            if(paddle_y+paddle_H <= WORLD_H)paddle_y = paddle_y + 10;
			break;
        }
    }
    public void keyReleased(KeyEvent e){
        switch(e.getKeyCode()){
            case KeyEvent.VK_UP:
		    	break;
		    case KeyEvent.VK_DOWN:
			    break;
        }
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Pong");
        frame.getContentPane().setBackground(Color.black);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Pong canvas = new Pong();
        frame.add(canvas);
        frame.pack();
        frame.setVisible(true);
        new Thread(canvas).start();
    }
}