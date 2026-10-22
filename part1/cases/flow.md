flowchart TD
    A([Start]) --> B[/Input two numbers/]
    B --> C{A > B?}
    C -- Yes --> D[/Print A/]
    C -- No --> E[/Print B/]
    D --> F([End])
    E --> F
