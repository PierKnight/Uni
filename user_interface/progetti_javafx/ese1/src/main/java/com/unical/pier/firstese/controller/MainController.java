package com.unical.pier.firstese.controller;

import javafx.animation.RotateTransition;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.TextArea;
import javafx.scene.control.skin.ButtonSkin;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;
import javafx.util.Duration;

public class MainController {


    @FXML
    private VBox profileBox;
    @FXML
    private Button sendButton;

    @FXML
    private VBox readBox;

    @FXML
    private ScrollPane scrollViewPane;

    @FXML
    private TextArea writingArea;

    @FXML
    void onSendButton(ActionEvent event) {

        String text = writingArea.getText();


        Text t = new Text(text);
        t.setFont(new Font("sy",30));
        t.setTextAlignment(TextAlignment.RIGHT);
        readBox.getChildren().add(t);

        scrollViewPane.setVvalue(1.0D);



        writingArea.clear();


    }


    @FXML
    void initialize()
    {
        System.out.println("Eejewuitet");



        RotateTransition rotateTransition = new RotateTransition(Duration.INDEFINITE);
        rotateTransition.setNode(this.sendButton);
        rotateTransition.setByAngle(1);
        rotateTransition.play();
    }

}