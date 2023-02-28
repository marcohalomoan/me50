# Distinctiveness and Complexity

The project is completely different from the projects in CS50W since it is not intended to communicate with others. Instead, its goal is to provide a platform to aid chess players and communities to organize and participate in tournaments more easily. It is more complex than network (I believe the hardest project in the course) since each tournament has way more attributes than post in network, for example location, time control, slots, participant, and more. The attributes also affect the display in many ways such as when number participants equal to slots, the tournament page is closed, similarly when the tournament date has passed. Other than listing tournaments and sign up for them, the organizer can submit tournament report and the results for all tournaments are displayed in separate page. The result include the podium winners and number of points for each participant.


# Content

There are login, register, logout pages that are self explanatory. There are 7 other html templates excluding login and register: Layout, Index, Results, Tournament_register, tournament_result, tournament, and upload_result.
- Layout contains navigation bar
- Index list all available tournaments (not passed deadline, not closed by organizer, and not full)
- Results list all finished tournament results
- Tournament_register contains form to add new tournament
- tournament_result, from the result page, clicking on one of the result brings user to this page to view more detailed report
- tournament, from index, clicking on one of the tournament takes user to tournament details and apply feature
- upload_result, enter tournament results for each player (points)

Besides the html, there are django python files, styles.css, and chesstourney.js.
Chesstourney.js contains all the eventlisteners for various buttons and also validate some input, like tournament date can't be in the past. It also have asynchronous requests to some of views.py api to list all the players name when uploading result (could not use normal form since every tournaments have different participants and number of participants)
