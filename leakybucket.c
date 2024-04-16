#include <stdio.h>

int main() {
  int bucket_size, outgoing_rate, n, incoming, store = 0;

  printf("Enter bucket size (in bytes): ");
  scanf("%d", &bucket_size);

  printf("Enter outgoing rate (in bytes/unit time): ");
  scanf("%d", &outgoing_rate);

  printf("Enter number of incoming packets: ");
  scanf("%d", &n);

  while (n != 0) {
    printf("Enter the incoming packet size (in bytes): ");
    scanf("%d", &incoming);

    printf("Incoming packet size: %d\n", incoming);

    // Check if incoming packet fits in the buffer
    if (incoming <= (bucket_size - store)) {
      store += incoming; // Add packet to buffer
      printf("Bucket buffer size: %d out of %d\n", store, bucket_size);
    } else {
      int dropped_packets = (incoming - (bucket_size - store)) / outgoing_rate;
      printf("Dropped %d packets\n", dropped_packets);
      printf("Bucket buffer size: %d out of %d\n", store, bucket_size);
      store = bucket_size; // Set buffer to max capacity (simulate dropping)
    }

    store = store - outgoing_rate; // Simulate outgoing transmission
    if (store < 0) {
      store = 0; // Prevent negative buffer size
    }
    printf("After outgoing: %d packets left out of %d in buffer\n", store, bucket_size);
    n--;
  }

  return 0;
}
