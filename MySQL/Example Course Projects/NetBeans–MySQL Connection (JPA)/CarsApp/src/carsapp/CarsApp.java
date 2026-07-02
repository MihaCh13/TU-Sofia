/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package carsapp;
import gui.*;
import javax.swing.JFrame;

/**
 *
 * @author User
 */
public class CarsApp {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        JFrame main = new JFrame();
        main.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        NewJPanel np = new NewJPanel();
        main.setContentPane(np);
        main.pack();
        main.setVisible(true);
 
    }
    
}
