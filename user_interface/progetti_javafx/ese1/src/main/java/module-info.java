module com.unical.pier.firstese {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.unical.pier.firstese to javafx.fxml;
    exports com.unical.pier.firstese;
}