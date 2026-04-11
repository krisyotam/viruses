/*
  name      Out of Control
  type      prank
  cve       —
  year      —
  os        cross-platform
  authors   Minhas Kamal
  source    https://github.com/MinhasKamal/CuteVirusCollection
  archived  krisyotam
  notes     random mouse movement via Java Robot
 */

// Developer: Minhas Kamal
// Randomly moves the mouse pointer, & clicks different places on the screen.

import java.awt.Robot;
import java.awt.event.InputEvent;
import java.util.Random;

public class out_of_control {
    public static void main(String[] args) throws Exception {
        Robot robot = new Robot();
        Random random = new Random();
        while(true){
            robot.mouseMove(random.nextInt(1200), random.nextInt(700));
            Thread.sleep(300);
        }
    }
}
