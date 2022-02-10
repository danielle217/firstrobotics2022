// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/XboxController.h>
#include "iostream"
bool arcadeMode = false;
bool updateDriveMode = true;


using namespace std;
/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with tank steering.
 */
class Robot : public frc::TimedRobot {
  frc::PWMSparkMax m_leftMotor{0};
  frc::PWMSparkMax m_rightMotor{1};
  frc::Spark m_elevator{2};
  frc::Spark m_pickup {3};
  frc::PWMSparkMax m_shootera{4};
  frc::PWMSparkMax m_shooterb{5};
  frc::DifferentialDrive m_robotDrive{m_leftMotor, m_rightMotor};
  frc::DifferentialDrive m_ballshooter{m_shootera,m_shooterb};
  frc::Joystick m_leftStick{0};
  frc::Joystick m_rightStick{1};
  frc::XboxController m_drivecontroller {0};

 public:
  void RobotInit() override {
    
    
    // We need to invert one side of the drivetrain so that positive voltages
    // result in both sides moving forward. Depending on how your robot's
    // gearbox is constructed, you might have to invert the left side instead.
    m_rightMotor.SetInverted(true);
  }
  void OutputDriveMode() {
    if (arcadeMode)
    {
      cout << "arcade mode activated" << endl;
    }
    else {
      cout << "tank mode activated" << endl;
    }
  }

  void SetDriveMode() {
    if (m_drivecontroller.GetBButtonPressed() && updateDriveMode) {
      arcadeMode = !arcadeMode;
      OutputDriveMode();
      updateDriveMode = false;
    }
    else {
      updateDriveMode = true;
    }
  }
  void MoveElevator() {
    if (m_drivecontroller.GetLeftTriggerAxis() && !m_drivecontroller.GetRightTriggerAxis()) 
    {
      // TODO: Add elevator up control
       m_elevator.Set(1);
      cout << "moving elevator up" << endl;
    }
    else if (m_drivecontroller.GetRightTriggerAxis() && !m_drivecontroller.GetLeftTriggerAxis())
    {
       m_elevator.Set(-1);

      // TODO: add elevator down control
      cout << "moving elevator down" << endl;
    }
    else {
      m_elevator.Set(0);

      // TODO: Stop elevator 
    }
  }
  void PickupBall() {
 
 if (m_drivecontroller.GetLeftBumperPressed() && !m_drivecontroller.GetRightBumperPressed()) 
    {
      m_pickup.Set(1);
      cout << "picking up" << endl;
    }
    else if (m_drivecontroller.GetRightBumperPressed() && !m_drivecontroller.GetLeftBumperPressed())
    {
       m_pickup.Set(-1);
        cout << "dropping down" << endl;
      // TODO: add pickup control
    }
    else {
      m_pickup.Set(0);
  }
  }
  void ShootBall() {

  }

  void TeleopPeriodic() override {
    // Drive with tank style
      SetDriveMode();
      MoveElevator();
      PickupBall();
    if (!arcadeMode)
    {
     m_robotDrive.TankDrive(m_drivecontroller.GetLeftY(), m_drivecontroller.GetRightY());
    } else
    {
        m_robotDrive.ArcadeDrive(
          m_drivecontroller.GetLeftY(), m_drivecontroller.GetRightX()
        );
    }

  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
