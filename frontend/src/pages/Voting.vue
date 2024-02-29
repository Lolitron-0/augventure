<template>
  <div class="back">
    <div class="profile">
      <div class="container_for_navbar">
        <img :src="events.picture_url" alt="" class="ellipse_logo"/>
        <div class="title_event">{{ events.title }}</div>
        <i class='bx bx-dots-horizontal-rounded' id="dotes-icon" v-if="show" @click="Show" key="dotes"></i>
        <div class="description_event" v-else>{{ events.description }}</div>
      </div>

      <div class="container_for_blocks_profile">
        <div class="sprint_history">
          <div class="title_for_sprint_history">Sprint history</div>
          <div class="container_for_sprints">

          </div>
        </div>

        <div class="voting_chat">
          <div class="title_for_voting_chat" v-if="events.state === 'in_progress'">Voting in progress...</div>
          <div class="title_for_voting_chat" v-else>Voting results</div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      events: {},
      descriptionVisible: false,
      show: true,
    }
  },
  async beforeMount() {
    try {
      const ID = this.$route.params.id;
      const ev = await this.$api.events.getOne(ID);
      this.events = ev.data.event

    } catch (error) {
      console.log('failed:', error);
    }
  },
  methods: {
    toggleDescription() {
      this.descriptionVisible = !this.descriptionVisible;
    },
    Show() {
      this.show = !this.show;
    },
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
.container_for_blocks_profile {
  position: relative;
  width: 100%;
  height: 100%;
}
.sprint_history {
  position: absolute;
  left: 0;
  border: 2px solid var(--border-light-gray-color);
  border-radius: 5px;
  width: 25%;
  height: 80vh;
  //padding: 2%;
}

.voting_chat {
  position: absolute;
  left: 28%;
  border: 2px solid var(--border-light-gray-color);
  border-radius: 5px;
  width: 72%;
  height: 80vh;
  //padding: 0 10px 10px 10px;
}

.container_for_navbar {
  //border: 1px solid red;
  top: 0;
  width: 100%;
  position: relative;
  height: 50px;
  display: flex;
  justify-content: left;
  align-items: center;
  gap: 30px;
  border-bottom: 1px solid var(--border-light-gray-color);
  padding: 5px 10px;
  color: #cfcfcf;
  margin-bottom: 15px;
}

.title_for_sprint_history {
  color: var(--text-wight-color);
  width: 100%;
  height: 40px;
  font-size: 18px;
  position: absolute;
  align-items: center;
  justify-content: center;
  background-color: var(--navbar-color);
  border-bottom: 1px solid var(--border-light-gray-color);
  display: flex;
  border-radius: 5px;
}

.title_for_voting_chat {
  color: var(--text-wight-color);
  width: 100%;
  font-size: 18px;
  height: 40px;
  position: absolute;
  display: flex;
  align-items: center;
  justify-content: center;
  background-color: var(--navbar-color);
  border-bottom: 1px solid var(--border-light-gray-color);
  border-radius: 5px;
}

.ellipse_logo {
  height: 90%;
  border: 1px solid #858585;
  box-sizing: border-box;
  background-color: #0e73bd;
  cursor: pointer;
  border-radius: 50%;
  aspect-ratio: 1;
}

.title_event {
  font-size: 18px;
}

.title_event::first-letter {
  text-transform: uppercase;
}

.description_event {

}
</style>