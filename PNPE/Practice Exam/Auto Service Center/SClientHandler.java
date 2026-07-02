import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.EOFException;
import java.io.IOException;
import java.net.Socket;
import java.util.List;

/**
 * Обслужва един клиент в отделна нишка.
 *
 * Протокол (примерен):
 *
 * Команда 1 – регистриране на нова поръчка:
 *   client -> server:
 *     int 1
 *     UTF carRegNumber
 *     UTF description
 *
 *   server -> client:
 *     boolean success
 *     int id (или -1 при грешка)
 *     UTF message
 *
 * Команда 2 – промяна на статус:
 *   client -> server:
 *     int 2
 *     int id
 *     UTF newStatus
 *
 *   server -> client:
 *     boolean success
 *     UTF message
 *
 * Команда 3 – справка по статус:
 *   client -> server:
 *     int 3
 *     UTF status
 *
 *   server -> client:
 *     int count
 *     (повтаря се count пъти)
 *        int id
 *        UTF carRegNumber
 *        UTF description
 *        UTF status
 *
 * Друга стойност за команда или EOF -> затваряне на връзката.
 */
public class ClientHandler extends Thread {

    private final Socket socket;
    private final ServiceCenter serviceCenter;

    public ClientHandler(Socket socket, ServiceCenter serviceCenter) {
        this.socket = socket;
        this.serviceCenter = serviceCenter;
    }

    @Override
    public void run() {
        System.out.println("Client connected: " + socket.getRemoteSocketAddress());
        try (Socket s = socket;
             DataInputStream in = new DataInputStream(s.getInputStream());
             DataOutputStream out = new DataOutputStream(s.getOutputStream())) {

            while (true) {
                int command;
                try {
                    command = in.readInt();
                } catch (EOFException eof) {
                    // клиентът е затворил връзката
                    break;
                }

                if (command == 1) {
                    handleRegisterOrder(in, out);
                } else if (command == 2) {
                    handleChangeStatus(in, out);
                } else if (command == 3) {
                    handleListByStatus(in, out);
                } else {
                    // непозната команда или сигнал за край – спираме
                    break;
                }
            }

        } catch (IOException e) {
            System.out.println("Error with client " + socket.getRemoteSocketAddress()
                    + ": " + e.getMessage());
        } finally {
            System.out.println("Client disconnected: " + socket.getRemoteSocketAddress());
        }
    }

    /**
     * TODO 4:
     * Обработка на команда 1 – регистриране на нова поръчка.
     *
     * Вход (от клиента):
     *   UTF carRegNumber
     *   UTF description
     *
     * Логика:
     *   - извикване на serviceCenter.registerOrder(...)
     *   - връщане към клиента:
     *       boolean success (true)
     *       int id (генерираното id)
     *       UTF message
     *
     * По желание: може да се добави проверка за вече активна поръчка.
     */
    private void handleRegisterOrder(DataInputStream in, DataOutputStream out) throws IOException {
        throw new UnsupportedOperationException("TODO 4: имплементирайте handleRegisterOrder");
    }

    /**
     * TODO 5:
     * Обработка на команда 2 – смяна на статус.
     *
     * Вход (от клиента):
     *   int id
     *   UTF newStatus
     *
     * Логика:
     *   - извикване на serviceCenter.changeStatus(id, newStatus)
     *   - връщане:
     *       boolean success
     *       UTF message (например 'OK' или 'Няма поръчка с такова ID')
     */
    private void handleChangeStatus(DataInputStream in, DataOutputStream out) throws IOException {
        throw new UnsupportedOperationException("TODO 5: имплементирайте handleChangeStatus");
    }

    /**
     * TODO 6:
     * Обработка на команда 3 – справка по статус.
     *
     * Вход (от клиента):
     *   UTF status
     *
     * Логика:
     *   - извикване на serviceCenter.getOrdersByStatus(status)
     *   - връщане към клиента:
     *       int count
     *       повторение count пъти:
     *          int id
     *          UTF carRegNumber
     *          UTF description
     *          UTF status
     */
    private void handleListByStatus(DataInputStream in, DataOutputStream out) throws IOException {
        throw new UnsupportedOperationException("TODO 6: имплементирайте handleListByStatus");
    }
}
