<template>
  <div class="back">
    <div class="profile">
      <div class="container_for_navbar">
        jnwedkwcfjwdnwskdjdnswmwskwdjnmsjhndsmaqqsdwhnm,lJHBM XM,LJWNDC MSXA,LQWJHB
      </div>

      <div class="sprint_history">
        <div class="title_for_sprint_history">Sprint history</div>
        <div class="container_for_sprints">

        </div>
      </div>

      <div class="voting_chat">
        <div class="title_for_voting_chat">{{ title }}</div>


      </div>
    </div>
  </div>
</template>

<script>

export default {
  data() {
    return {
      title: "Voting in progress..."
    }
  }
}
</script>

<style scoped>
@import "@/styles.css";


hr {
  margin-top: 5px;
  background-color: var(--border-light-gray-color);
  padding: .3px;
  border: var(--border-light-gray-color);
}

.back {
  /* background-color: #0d1117; */
  background-color: var(--background-app-color);
  position: fixed;
  width: 100vw;
  max-height: 100vh;
  height: 100vh;
  padding: 80px 5% 24px 5%;
  overflow-y: auto;
  overflow-x: hidden;

}

.profile {
  position: absolute;
  //border: 1px solid red;
  width: 85vw;
  height: 100%;
}

.sprint_history {
  position: absolute;
  top: 50px;
  left: 0;
  border: 1px solid #31a0a8;
  width: 25%;
  height: 80vh;
  //padding: 2%;
}

.voting_chat {
  position: absolute;
  top: 50px;
  left: 25%;
  border: 1px solid #cfcfcf;
  width: 75%;
  height: 80vh;
  //padding: 0 10px 10px 10px;
}

.container_for_navbar {
  border: 1px solid red;
  top: 0;
  width: 100%;
  position: absolute;
  height: 50px;
  display: flex;
  justify-content: left;
  gap: 50px;
  border-bottom: 1px solid var(--border-light-gray-color);
  padding: 5px 10px;
  color: #cfcfcf;
  margin-bottom: 15px;
}

.title_for_sprint_history {
  color: var(--text-wight-color);
  border: 0.5px solid green;
  width: 100%;
  height: 50px;
  position: absolute;
  align-items: center;
  justify-content: center;
  background-color: var(--navbar-color);
  border-bottom: 2px solid var(--border-light-gray-color);
}

.title_for_voting_chat {
  color: var(--text-wight-color);
  border: 0.5px solid greenyellow;
  width: 100%;
  height: 50px;
  position: absolute;
  align-items: center;
  justify-content: center;
  background-color: var(--navbar-color);
  border-bottom: 2px solid var(--border-light-gray-color);

}
</style>