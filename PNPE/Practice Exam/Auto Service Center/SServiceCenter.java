import java.util.ArrayList;
import java.util.List;

/**
 * Споделен обект, който държи всички поръчки.
 * Тук се очаква използване на synchronized.
 */
public class ServiceCenter {

    private final List<RepairOrder> orders = new ArrayList<>();
    private int nextId = 1;

    /**
     * TODO 1:
     * Регистрира нова поръчка със статус "NEW" и връща генерираното id.
     *
     * Примерна логика:
     *   - вземи текущото nextId и го запази в локална променлива id
     *   - увеличи nextId
     *   - създай нов RepairOrder(id, carRegNumber, description, "NEW")
     *   - добави го в списъка orders
     *   - върни id
     *
     * Методът трябва да е synchronized, за да е безопасен при много нишки.
     */
    public synchronized int registerOrder(String carRegNumber, String description) {
        throw new UnsupportedOperationException("TODO 1: имплементирайте registerOrder");
    }

    /**
     * TODO 2:
     * Променя статуса на поръчка с дадено id на newStatus.
     * Връща true при успех, false ако няма такава поръчка.
     *
     * Примерна логика:
     *   - обхождане на orders
     *   - ако order.getId() == id:
     *       order.setStatus(newStatus);
     *       return true;
     *   - в края: return false;
     *
     * Методът трябва да е synchronized.
     */
    public synchronized boolean changeStatus(int id, String newStatus) {
        throw new UnsupportedOperationException("TODO 2: имплементирайте changeStatus");
    }

    /**
     * TODO 3:
     * Връща НОВ списък с всички поръчки със статус, равен на подадения (case-insensitive).
     *
     * Примерна логика:
     *   List<RepairOrder> result = new ArrayList<>();
     *   за всяка order в orders:
     *       ако order.getStatus().equalsIgnoreCase(status):
     *           добави в result
     *   върни result
     *
     * Методът трябва да е synchronized.
     */
    public synchronized List<RepairOrder> getOrdersByStatus(String status) {
        throw new UnsupportedOperationException("TODO 3: имплементирайте getOrdersByStatus");
    }

    /**
     * НЕ е задължително за условието, но помага за проверка.
     * По избор може да се имплементира от студента.
     */
    public synchronized List<RepairOrder> getAllOrders() {
        return new ArrayList<>(orders);
    }
}
