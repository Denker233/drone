# CSCI 3081 Project - Drone Simulation System

# Team number, member names, and x500

Team number: 31

Minrui Tian – tian0138

Zixi Zhu – zhu00463

Zhao Liu – liu01570

# Project Brief
The project is to simulate the behavior of various entities. The two main entities we focus on are robots and the drone. The user is able to set the pickup location, the final destination of the robot, and the routing strategy. Afterward, the drone will head to the robot and pick it up. Then, it will take the robot to the destination with the routing strategy of choice. When the robot arrives at the set destination, it will celebrate by rotating or jumping or first rotating and then jumping based on your strategy of choice. The project will also simulate a car, a high-speed car, and a helicopter that can all move around randomly. And there is a button to create a helicopter in the simulation map.


This directory contains the support code needed to visualize the drone simulation system.

#### What is in this directory?
<ul>
  <li>  <code>README.md</code>
  <li>  <code>.gitignore</code>
  <li>  <code>app</code> folder, which contains:
    <ul>
      <li>  <code>graph_viewer</code> : producing graph visualization
      <li>  <code>transit_service</code> : visualization
    </ul>
  <li>  <code>libs</code> folder, which contains:
    <ul>
      <li>  <code>routing</code> : finding the paths
      <li>  <code>trainsit</code> : entities properties
    </ul>
  <li>  <code>dependencies</code>
</ul>

## Getting Started

Here is a quick overview of how to run the visualization (If you are using ssh, navigate to ssh category below):

    ```bash
    # Go to the project directory
    cd /path/to/repo/project
    
    # Build the project
    make -j
    
    # Run the project (./build/web-app <port> <web folder>)
    ./build/bin/transit_service 8081 apps/transit_service/web/
    ```
    
Navigate to http://127.0.0.1:8081 and you should see a visualization.

Navigate to http://127.0.0.1:8081/schedule.html and you should see a page to schedule the trips.

Below are instructions that detail how to build and run in several different environments.  

## Getting Started using SSH onto CSE Lab machines

1. SSH into a CSE Lab Machine using **port forwarding** for the UI

   **Note:** If port `8081` is not available, choose a different port (e.g. 8082, 8083, etc...)

    ```bash
    ssh -L 8081:127.0.0.1:8081 x500@csel-xxxx.cselabs.umn.edu
    ```
    
    Example:
    ```bash
    ssh -L 8081:127.0.0.1:8081 kaung006@csel-kh1250-05.cselabs.umn.edu
    ```

2. Compile the project (within ssh session)

    ```bash
    cd /path/to/repo/project
    make -j
    ```
    
 2. Run project (within ssh session)

    ```bash
    ./build/bin/transit_service 8081 apps/transit_service/web/
    ```

5. Navigate to http://127.0.0.1:8081 and you should see a visualization.

6. Navigate to http://127.0.0.1:8081/schedule.html and you should see a page to schedule the trips.

# Simulation

## Schedule
You will be able to schedule the robots for a ride in this page http://127.0.0.1:8081/schedule.html. 

Type passenger name, select start and end destination, and press `Schedule Trip` button to schedule a trip. 

Now go to 3D Visualization page and select the view of the entities on top right corner.

There is also a `Add Helicoptor` botton below in this page http://127.0.0.1:8081/schedule.html.

By pressing it, you will be able to see a helicopter on the 3D simulation page.

## 3D Visualization
You will be able to watch the simulation of the drone and the passenger here http://127.0.0.1:8081.

There will also be a car, a high speed car and a helicopter that all move around randomly in the same simulation page.

On top right corner, you can change your camera view into locking the entities and the speed of simulation and you can also show all the routes the strategy can take by checking the `Show All Routes` box.

# New Feature

## Functionality
We add a swappable electronic booster that attaches to the drone. The booster has a separate battery that power itself. And we assume that the drone has a solar panel that can maintain a speed of 10. The booster can speed up the drone from 10 to 100. And there are booster swap stations on the map that can replace the booster on the drone with a fully charged battery. The booster is on by default but when the drone picks up the robot, it will select the least time-consuming route to go(whether to go to the swap station and which swap station to go to).

## Significance
In the real world, customers may need fast delivery service with limited resources(a booster that can run out of battery in our case). And it is not always the case that with the limited resource we can go to the destination faster and heading to swap a booster may lead to late delivery. So it must be evaluated case by case to improve the customer experience. Our new feature is meant to simulate real-world situations.

## Implementation
We create a new entity called Station and allocate a few of them on the map. We add a BoosterDecorator that will change the speed of the drone based on the battery status and the battery status will be updated each time the move() is called. Also, in each Strategy(Astar, DFS, and Dijkstra) that the drone can use after picking up the robot, we add RealDistance() and TimeDirect(), and TimeSwap() to calculate how much time each route will spend and compare them to get the least time-consuming route in the decision. Then the drone will take the robot to the destination with the least time-consuming route.

## Design Patterns
Decorator pattern: 

Solid:
1. Our booster feature is to speed up the drone and extends its existing behavior so we can add this extra behavior at runtime on the existing code so that we can save some effort building a whole new subclass. 
2. It is more portable. The decorator can be added or removed at the run time.
3. We can also combine multiple decorators. In our case, we could add our BoosterDecorator to the existing Spin/JumpDecorator so that we can have many features for one object.

Abstract Factory Pattern:
1. Compatibility: The station produced from StationFactory are compatible with our other entities 
2. Low coupling: The new StationFactory and its products-stations don’t depend on other concrete classes of those products so it allows future extensibility. If there are some bugs in our newly added StationFactory or Station, it won’t affect the existing entities or factories and vice versa.  

## Instructions
Not user interactable.

# Sprint retrospective
We use Atlassian’s Jira as the initial task board. Sprint does help in the initial process in terms of brainstorming how we disintegrate the whole development process into multiple small and achievable parts. However, not everything goes as planned, some steps take longer than we thought (many expected bugs when implementing the algorithm inside each strategy) and each teammate’s schedule is dynamic(newly released assignments from other courses) so adhering to the original schedule is not practical. And we don’t have the habit to check Jira every day so we may miss some information. Instead, we use social media platforms like WeChat a lot. Each teammate updates their process and can get a reply in a short amount of time. We would still use Sprint for brainstorming, task, and schedule making. And I think we would use Sprint more if we get into the industry and have a relatively set schedule.

# UML

<object data="https://github.umn.edu/umn-csci-3081-F22/Team-001-31-lab10/files/912/hw2.2.4.pdf" type="application/pdf" width="700px" height="700px">
    <embed src="https://github.umn.edu/umn-csci-3081-F22/Team-001-31-lab10/files/912/hw2.2.4.pdf">
        <p>This browser does not support PDFs. Please download the PDF to view it: <a href="https://github.umn.edu/umn-csci-3081-F22/Team-001-31-lab10/files/912/hw2.2.4.pdf">Download PDF</a>.</p>
    </embed>
</object>

<iframe width="100%" height="800" src="https://github.umn.edu/umn-csci-3081-F22/Team-001-31-lab10/files/912/hw2.2.4.pdf">

