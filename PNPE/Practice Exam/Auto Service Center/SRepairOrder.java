public class RepairOrder {

    private final int id;
    private final String carRegNumber;
    private final String description;
    private String status; // например "NEW", "IN_PROGRESS", "DONE"

    public RepairOrder(int id, String carRegNumber, String description, String status) {
        this.id = id;
        this.carRegNumber = carRegNumber;
        this.description = description;
        this.status = status;
    }

    public int getId() {
        return id;
    }

    public String getCarRegNumber() {
        return carRegNumber;
    }

    public String getDescription() {
        return description;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return "RepairOrder{" +
                "id=" + id +
                ", carRegNumber='" + carRegNumber + '\'' +
                ", description='" + description + '\'' +
                ", status='" + status + '\'' +
                '}';
    }
}
