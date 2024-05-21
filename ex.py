import simpy

class Process:
    def __init__(self, pid, at, bt):
        self.pid = pid
        self.at = at
        self.bt = bt
        self.tat = 0
        self.wt = 0

class NonPreemptiveSJF:
    def __init__(self, env, processes):
        self.env = env
        self.processes = processes
        self.current_time = 0
        self.finished_processes = []

    def run(self):
        self.processes.sort(key=lambda x: x.at)
        while self.processes:
            available_processes = [p for p in self.processes if p.at <= self.current_time]
            if available_processes:
                shortest_job = min(available_processes, key=lambda x: x.bt)
                self.current_time += shortest_job.bt
                shortest_job.tat = self.current_time - shortest_job.at
                shortest_job.wt = shortest_job.tat - shortest_job.bt
                self.finished_processes.append(shortest_job)
                self.processes.remove(shortest_job)
                yield self.env.timeout(shortest_job.bt)
            else:
                self.current_time = min(p.at for p in self.processes)

    def print_results(self):
        total_tat = 0
        total_wt = 0
        for process in self.finished_processes:
            total_tat += process.tat
            total_wt += process.wt
            print(f"Process {process.pid}: TAT={process.tat}, WT={process.wt}")
        print(f"Average TAT: {total_tat / len(self.finished_processes)}")
        print(f"Average WT: {total_wt / len(self.finished_processes)}")

# Example usage
if __name__ == "__main__":
    env = simpy.Environment()
    processes = [
        Process(1, 2, 6),
        Process(2, 5, 2),
        Process(3, 1, 8),
        Process(4, 0, 3),
        Process(5,4,4)
    ]
    scheduler = NonPreemptiveSJF(env, processes)
    env.process(scheduler.run())
    env.run()

    scheduler.print_results()










