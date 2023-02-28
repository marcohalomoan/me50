document.addEventListener('DOMContentLoaded', () => {
    add_participant()
    submit_result()
    show_tournament_details()
    validate_new_t()
})

function add_participant() {
    const apply = document.querySelector("#apply");
    if (apply !== null) {
        apply.addEventListener('click', () => {
            alert("You have successfully registered for the tournament")
        })
    }
}

function submit_result() {
    const upload_view = document.querySelector("#upload-result-view");
    const tournament = document.querySelector("#tournaments");
    if (tournament !== null) {
        const user_id = document.querySelector(".user-id").id;
        tournament.addEventListener('change', ()=> {
            const form = document.createElement("form");
            const tournament_id = event.currentTarget.value
            form.id = "tournament-result";
            fetch(`/get_participants/${tournament_id}`)
            .then(response => response.json())
            .then(participants => {
                for(let i=0; i < participants.length; i++) {
                    const individual_container = document.createElement("div");
    
                    individual_container.classList.add("card-body");
                    const name = document.createElement("h5")
                    name.innerHTML = participants[i].username;
    
                    const score = document.createElement("input");
                    score.type = "number";
                    score.step = 0.5;
                    score.id = `score-${participants[i].id}`;
                    score.min = 0;
    
                    individual_container.append(name, score);
                    form.append(individual_container);
                }
                const submit = document.createElement("button");
                submit.type = "submit";
                submit.innerHTML = "Submit Result";
                submit.classList.add("btn", "btn-info");
                form.append(submit)
                form.addEventListener('submit', () => {
                    event.preventDefault()
                    var total_scores = [];
                    for(let i=0; i < participants.length; i++) {
                        var final_score = document.querySelector(`#score-${participants[i].id}`).value
                        total_scores.push(final_score);
                    }
                    console.log(participants);
                    fetch(`/submit_result/${user_id}`, {
                      method: 'POST',
                      body: JSON.stringify({
                          players: participants,
                          participants_score: total_scores,
                          tournament: tournament_id
                      })
                    })
                    location.replace("/results");
            })
            })
            upload_view.append(form);
        })
    }
}

function show_tournament_details() {
    const details = document.querySelector(".details-view");
    const details_button = document.querySelector("#tour-details");
    if (details !== null && details_button !== null) {
        details_button.addEventListener('click',() => {
            if (details.style.display == "none") {
                details.style.display = "block";
            }
            else {
                details.style.display = "none";
            }
        })
    }
}

function validate_new_t() {
    const date_input = document.querySelector("#date");
    if (date_input !== null) {
        const date = new Date();

        let day = date.getDate();
        let month = date.getMonth() + 1;
        if (month.toString.length == 1) {
            month = `0${month}`;
        }
        if (day.toString.length == 1) {
            day = `0${day}`;
        }
        let year = date.getFullYear();
    
        let currentDate = `${year}-${month}-${day}`;
        date_input.addEventListener('change', () => {
            if (event.currentTarget.value < currentDate) {
                alert("Tournament date can't be in the past");
                event.currentTarget.value = '';
            }
        })
    }
    
}