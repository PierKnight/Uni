module com.pier.book_register {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires validatorfx;

    opens com.pier.book_register to javafx.fxml;
    exports com.pier.book_register;

    exports com.pier.book_register.controller;
    opens com.pier.book_register.controller to javafx.fxml;

    opens com.pier.book_register.view to javafx.fxml;
    exports com.pier.book_register.view;
}