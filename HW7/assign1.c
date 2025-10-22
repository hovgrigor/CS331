#include <stdio.h>
#include <stdlib.h>

struct Process {
  int pid;
  int arrival_time;
  int burst_time;
  int turnaround_time;
  int waiting_time;
  int response_time;
  int completed;
};

// For qsort
int compare_by_arrival(const void *a, const void *b) {
  struct Process *p1 = (struct Process *)a;
  struct Process *p2 = (struct Process *)b;
  return (*p1).arrival_time - (*p2).arrival_time;
}

// Display Functions
void print_results(struct Process p[], int n) {
  double total_wt = 0;
  double total_tat = 0;
  double total_rt = 0;

  printf("\nPID\tAT\tBT\tWT\tTAT\tRT\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival_time,
           p[i].burst_time, p[i].waiting_time, p[i].turnaround_time,
           p[i].response_time);

    total_wt += p[i].waiting_time;
    total_tat += p[i].turnaround_time;
    total_rt += p[i].response_time;
  }

  printf("\nAverage Waiting Time: %.2f", total_wt / n);
  printf("\nAverage Turnaround Time: %.2f", total_tat / n);
  printf("\nAverage Response Time: %.2f\n", total_rt / n);
}

void print_processes(int order[], int start_time[], int end_time[], int n) {
  printf("\nGantt Chart:\n|");
  for (int i = 0; i < n; i++) {
    printf(" P%d |", order[i]);
  }
  printf("\n");
}

void fcfs(struct Process p[], int n) {
  struct Process temp;
  int current_time = 0;
  int order[n];
  int start[n];
  int end[n];

  qsort(p, n, sizeof(temp), compare_by_arrival);

  for (int i = 0; i < n; i++) {
    if (current_time < p[i].arrival_time)
      current_time = p[i].arrival_time;

    start[i] = current_time;
    current_time += p[i].burst_time;
    end[i] = current_time;

    p[i].turnaround_time = current_time - p[i].arrival_time;
    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
    p[i].response_time = p[i].waiting_time;

    order[i] = p[i].pid;
  }

  print_processes(order, start, end, n);
  print_results(p, n);
}

void sjf(struct Process p[], int n) {
  struct Process temp[n];
  for (int i = 0; i < n; i++) {
    temp[i] = p[i];
    temp[i].completed = 0;
  }

  int completed = 0;
  int current_time = 0;
  int order[n];
  int start[n];
  int end[n];
  int index = 0;

  while (completed < n) {
    int min_index = -1;
    int min_burst = 9999;

    // Find the process with the smallest burst time that has arrived
    for (int i = 0; i < n; i++) {
      if (temp[i].arrival_time <= current_time && !temp[i].completed) {
        if (temp[i].burst_time < min_burst) {
          min_burst = temp[i].burst_time;
          min_index = i;

          // tie breaking, choose the process that arrived earlier
        } else if (temp[i].burst_time == min_burst &&
                   temp[i].arrival_time < temp[min_index].arrival_time) {
          min_index = i;
        }
      }
    }

    // no process to schedule, move on
    if (min_index == -1) {
      current_time++;
      continue;
    }

    start[index] = current_time;
    order[index] = temp[min_index].pid;
    current_time += temp[min_index].burst_time;
    end[index] = current_time;

    temp[min_index].turnaround_time =
        current_time - temp[min_index].arrival_time;
    temp[min_index].waiting_time =
        temp[min_index].turnaround_time - temp[min_index].burst_time;
    temp[min_index].response_time = temp[min_index].waiting_time;
    temp[min_index].completed = 1;

    completed++;
    index++;
  }

  print_processes(order, start, end, n);
  print_results(temp, n);
}

int main() {
  int n;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  struct Process p[n];

  for (int i = 0; i < n; i++) {
    p[i].pid = i + 1;
    printf("Enter the arrival time and burst time for process %d: ", p[i].pid);
    scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    p[i].completed = 0;
  }

  printf("\n=== First Come First Served (FCFS) ===\n");
  fcfs(p, n);

  printf("\n=== Shortest Job First (SJF) ===\n");
  sjf(p, n);

  return 0;
}
