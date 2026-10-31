# Deadlock Detection and Recovery Simulator

A multi-page neon-themed educational website built with HTML, CSS, and JavaScript.

## Pages
- `index.html` — landing page
- `simulator.html` — editable allocation/request matrices, detection, and simulated recovery
- `resource-graph.html` — example resource allocation graph
- `recovery.html` — recovery strategies
- `theory.html` — deadlock conditions and algorithm
- `about.html` — project overview
- `contact.html` — local demo feedback form

## Run locally
1. Extract the ZIP.
2. Open the folder in Visual Studio Code.
3. Open `index.html` directly in a browser, or use the Live Server extension.
4. Go to Simulator and choose **Load example**, then **Run detection**.
5. To test recovery, select a detected unfinished process and click **Terminate selected deadlocked process**, then run detection again.

## Notes
- The site is frontend-only; no server or database is required.
- All processes/resources are simulated.
- The detection page assumes that the supplied Available vector is consistent with the allocation data.
- The simulator demonstrates process termination and resource release; it does not affect real operating-system processes.
