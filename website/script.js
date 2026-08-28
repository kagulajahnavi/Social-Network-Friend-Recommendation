// Smooth Scrolling

document.querySelectorAll('a[href^="#"]').forEach(anchor => {

    anchor.addEventListener("click", function(e){

        e.preventDefault();

        document.querySelector(this.getAttribute("href"))
        .scrollIntoView({
            behavior:"smooth"
        });

    });

});


// Fade-in Animation

const cards = document.querySelectorAll(".card");

const observer = new IntersectionObserver(entries=>{

    entries.forEach(entry=>{

        if(entry.isIntersecting){

            entry.target.style.opacity="1";
            entry.target.style.transform="translateY(0)";

        }

    });

});

cards.forEach(card=>{

    card.style.opacity="0";
    card.style.transform="translateY(50px)";
    card.style.transition="0.8s";

    observer.observe(card);

});

// ==========================
// Social Network Data
// ==========================

let users = [];
let friendships = {};
let network;

// ==========================
// Add User
// ==========================

function addUser() {

    let id = document.getElementById("userId").value;
    let name = document.getElementById("userName").value;

    if(id=="" || name==""){
        alert("Please enter User ID and Name");
        return;
    }

    for(let i=0;i<users.length;i++){
        if(users[i].id==id){
            alert("User ID already exists!");
            return;
        }
    }

    users.push({
        id:id,
        name:name
    });

    friendships[id]=[];

    alert("User Added Successfully!");
    updateGraph();

    document.getElementById("userId").value="";
    document.getElementById("userName").value="";

}

// ==========================
// Display Users
// ==========================

function displayUsers(){

    let output=document.getElementById("output");

    if(users.length==0){
        output.innerHTML="<h3>No Users Added!</h3>";
        return;
    }

    let html="<h3>Users List</h3>";

    for(let i=0;i<users.length;i++){

        html+=`
        <div style="padding:10px;border:1px solid #00bfff;margin:10px;border-radius:10px;">
            <b>ID :</b> ${users[i].id}<br>
            <b>Name :</b> ${users[i].name}
        </div>
        `;

    }


    output.innerHTML=html;

}
// ==========================
// Add Friendship
// ==========================

function addFriendship(){

    let u1 = document.getElementById("friend1").value;
    let u2 = document.getElementById("friend2").value;

    if(u1=="" || u2==""){
        alert("Enter both User IDs!");
        return;
    }

    if(!(u1 in friendships) || !(u2 in friendships)){
        alert("User ID not found!");
        return;
    }

    if(u1==u2){
        alert("A user cannot befriend themselves!");
        return;
    }

    if(friendships[u1].includes(u2)){
        alert("Friendship already exists!");
        return;
    }

    friendships[u1].push(u2);
    friendships[u2].push(u1);

    alert("Friendship Added Successfully!");
    updateGraph();

    document.getElementById("friend1").value="";
    document.getElementById("friend2").value="";
}

// ==========================
// Display Network
// ==========================

function displayNetwork(){

    let html = "<h3>Social Network</h3>";

    for(let id in friendships){

        let userName = "";

        for(let i=0;i<users.length;i++){
            if(users[i].id==id){
                userName = users[i].name;
                break;
            }
        }

        html += "<b>"+userName+" ("+id+")</b><br>";

        if(friendships[id].length==0){
            html += "No Friends";
        }else{

            for(let j=0;j<friendships[id].length;j++){

                let friendId = friendships[id][j];
                let friendName = "";

                for(let k=0;k<users.length;k++){
                    if(users[k].id==friendId){
                        friendName = users[k].name;
                        break;
                    }
                }

                html += "➡ " + friendName + " (" + friendId + ")<br>";
            }

        }

        html += "<hr>";
    }

    document.getElementById("networkOutput").innerHTML = html;
}

// ==========================
// Friend Recommendation (BFS)
// ==========================

function recommendFriends(){

    let id = document.getElementById("recommendUser").value;

    if(!(id in friendships)){
        alert("User not found!");
        return;
    }

    let recommendations = [];

    let directFriends = friendships[id];

    for(let i=0;i<directFriends.length;i++){

        let friend = directFriends[i];

        let friendsOfFriend = friendships[friend];

        for(let j=0;j<friendsOfFriend.length;j++){

            let candidate = friendsOfFriend[j];

            if(candidate != id &&
               !directFriends.includes(candidate) &&
               !recommendations.includes(candidate))
            {
                recommendations.push(candidate);
            }

        }

    }

    let html="<h3>Recommended Friends</h3>";

    if(recommendations.length==0){

        html+="No Recommendations Available.";

    }else{

        for(let i=0;i<recommendations.length;i++){

            let name="";

            for(let j=0;j<users.length;j++){

                if(users[j].id==recommendations[i]){
                    name=users[j].name;
                    break;
                }

            }

            html+="➡ "+name+" ("+recommendations[i]+")<br>";

        }

    }

    document.getElementById("recommendationOutput").innerHTML=html;

}
// ==========================
// Shortest Path (BFS)
// ==========================

function shortestPath(){

    let start = document.getElementById("startUser").value;
    let end = document.getElementById("endUser").value;

    if(!(start in friendships) || !(end in friendships)){
        alert("Invalid User IDs!");
        return;
    }

    let queue = [];
    let visited = {};
    let parent = {};

    queue.push(start);
    visited[start] = true;
    parent[start] = null;

    while(queue.length > 0){

        let current = queue.shift();

        if(current == end)
            break;

        for(let i=0;i<friendships[current].length;i++){

            let next = friendships[current][i];

            if(!visited[next]){

                visited[next] = true;
                parent[next] = current;
                queue.push(next);

            }

        }

    }

    let html = "<h3>Shortest Path</h3>";

    if(!visited[end]){

        html += "No Path Exists.";

    }else{

        let path = [];
        let temp = end;

        while(temp != null){

            path.push(temp);
            temp = parent[temp];

        }

        path.reverse();

        for(let i=0;i<path.length;i++){

            let name = "";

            for(let j=0;j<users.length;j++){

                if(users[j].id == path[i]){
                    name = users[j].name;
                    break;
                }

            }

            html += name + " (" + path[i] + ")";

            if(i != path.length-1)
                html += " ➜ ";

        }

    }

    document.getElementById("pathOutput").innerHTML = html;

}
// ==========================
// Search User
// ==========================

function searchUser(){

    let id = document.getElementById("searchId").value;

    let html = "";

    for(let i=0;i<users.length;i++){

        if(users[i].id==id){

            html = `
            <h3>User Details</h3>

            <p><b>ID :</b> ${users[i].id}</p>

            <p><b>Name :</b> ${users[i].name}</p>

            <p><b>Total Friends :</b> ${friendships[id].length}</p>
            `;

            document.getElementById("searchOutput").innerHTML = html;
            return;

        }

    }

    document.getElementById("searchOutput").innerHTML =
    "<h3>User Not Found!</h3>";

}

// ==========================
// Network Statistics
// ==========================

function showStatistics(){

    let totalUsers = users.length;

    let totalFriendships = 0;

    for(let id in friendships){
        totalFriendships += friendships[id].length;
    }

    totalFriendships = totalFriendships / 2;

    let average = 0;

    if(totalUsers > 0){
        average = (totalFriendships * 2 / totalUsers).toFixed(2);
    }

    document.getElementById("statsOutput").innerHTML = `
        <h3>Network Statistics</h3>

        <p><b>Total Users :</b> ${totalUsers}</p>

        <p><b>Total Friendships :</b> ${totalFriendships}</p>

        <p><b>Average Friends :</b> ${average}</p>
    `;
}
// ==========================
// Most Popular User
// ==========================

function mostPopularUser(){

    if(users.length == 0){

        document.getElementById("popularOutput").innerHTML =
        "<h3>No Users Available</h3>";

        return;
    }

    let maxFriends = -1;
    let popular = null;

    for(let i=0;i<users.length;i++){

        let id = users[i].id;

        if(friendships[id].length > maxFriends){

            maxFriends = friendships[id].length;
            popular = users[i];

        }

    }

    document.getElementById("popularOutput").innerHTML = `
        <h3>Most Popular User</h3>

        <p><b>ID :</b> ${popular.id}</p>

        <p><b>Name :</b> ${popular.name}</p>

        <p><b>Total Friends :</b> ${maxFriends}</p>
    `;
}
// ==========================
// Delete User
// ==========================

function deleteUser(){

    let id = document.getElementById("deleteId").value;

    if(!(id in friendships)){
        alert("User Not Found!");
        return;
    }

    // Remove from friends list
    for(let friend of friendships[id]){

        friendships[friend] = friendships[friend].filter(x => x != id);

    }

    delete friendships[id];

    users = users.filter(user => user.id != id);

    document.getElementById("deleteOutput").innerHTML =
    "<h3>User Deleted Successfully!</h3>";
    updateGraph();

}
const topBtn=document.getElementById("topBtn");

window.onscroll=function(){

if(document.body.scrollTop>300||document.documentElement.scrollTop>300){
topBtn.style.display="block";
}else{
topBtn.style.display="none";
}

};

topBtn.onclick=function(){
window.scrollTo({
top:0,
behavior:"smooth"
});
};

function updateGraph(){

    let nodes = [];
    let edges = [];

    for(let i=0;i<users.length;i++){

        nodes.push({
            id:users[i].id,
            label:users[i].name,
            shape:"dot",
            size:25,
            color:"#00bcd4",
            font:{
                size:18,
                color:"#000"
            }
        });

    }

    for(let id in friendships){

        for(let friend of friendships[id]){

            if(Number(id) < Number(friend)){

                edges.push({
                    from:id,
                    to:friend
                });

            }

        }

    }

    let container=document.getElementById("graphContainer");

    let data={
        nodes:new vis.DataSet(nodes),
        edges:new vis.DataSet(edges)
    };

    let options={

        physics:{
            enabled:true
        },

        nodes:{
            borderWidth:2
        },

        edges:{
            width:2
        }

    };

    network=new vis.Network(container,data,options);

}