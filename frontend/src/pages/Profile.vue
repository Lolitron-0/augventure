<template>
  <div class="back">
    <div class="profile">
      <info-block-for-profile
          :nickname="user.username"
      />
      <div class="body">
        <profile-navbar class="profileNavbar"></profile-navbar>
        <div class="form_for_btn_new">
          <router-link :to="{ name: 'newEvents' }">
            <button class="btn_new">New</button>
          </router-link>
        </div>
        <div class="container_for_event_forms">
          <event-form
              v-for="(event, index) in events"
              :key="index"
              :title="event.title"
              :description="event.description"
              :state="event.state"
              :likes="event.likes"
          />
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import MyButton from "@/components/UI/MyButton.vue";
import ProfileNavbar from "@/components/UI/ProfileNavbar.vue";
import EventForm from "@/components/UI/EventForm.vue";
import axios from 'axios'
import InfoBlockForProfile from "@/components/InfoBlockForProfile.vue";

export default {
  components: {InfoBlockForProfile, EventForm, ProfileNavbar, MyButton},

  data() {
    const user = JSON.parse(localStorage.getItem('user'));
    return {
      user: user,
      events: [],
    }
  },
  async mounted() {
    const options = {
      method: "GET",
      url: "/api/events",
      headers: {
        Authorization:
            localStorage.getItem("token")
      },
    };
    const events = await axios.request(options);
    for (const entry of events.data) {
      let descString = entry.event.description
      if (descString.length > 30) {
        descString = descString.slice(0, 30) + "..."
      }

      this.events.push({
        title: entry.event.title,
        description: descString,
        state: entry.event.state,
        likes: 6
      })
    }
  }
}
</script>

<style scoped>
@import '@/styles.css';

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
  /* border: 1px solid red; */
  width: 85vw;
  height: 100%;
}

.info {
  position: absolute;
  top: 0;
  left: 0;
  /* border: 1px solid #31a0a8; */
  width: 25%;
  height: 80vh;
  padding: 2%;
}

.body {
  position: absolute;
  top: 0;
  left: 25%;
  /* border: 1px solid #cfcfcf; */
  width: 75%;
  height: 80vh;
  padding: 0 10px 10px 10px;
}

.ellipse_nav_logo {
  width: 90%;
  height: 90%;
  /* padding-bottom: 90%; */
  max-width: 256px;
  max-height: 256px;
  border: solid 1px var(--border-light-gray-color);
  box-sizing: border-box;
  background-color: #0e73bd;
  cursor: pointer;
  border-radius: 50%;
  aspect-ratio: 1;
}

.profile_nickname {
  margin-top: 10px;
  color: #0e73bd;
  /* border: 1px solid red; */
  font-size: 22px;
}

.user_info {
  margin-top: 10px;
  color: #cfcfcf;
  /* border: 1px solid red; */
  display: flex;
  gap: 20%;
  justify-content: center;
}

.user_description {
  margin-top: 10px;
  color: #858585;
  /* border: 1px solid red; */
  font-size: 14px;
}

.your_subscribers {
  display: flex;
  flex-direction: column;
}

.profile_info_users_events {
  display: flex;
  flex-direction: column;
}

.subscriptions {
  display: flex;
  flex-direction: column;
}

.btn_new {
  font-size: 14px;
  letter-spacing: 1px;
  /* background: var(--text-turquoise-color); */
  background: green;
  padding: 2px 5px;
  text-decoration: none;
  /* text-transform: uppercase; */
  border-radius: 5px;
  transition: .6s;
  border: none;
  cursor: pointer;
  right: 10px;
  width: 60px;
  height: 30px;
  position: absolute;
}

/*.btn_new:hover {
  background-color: #31a0a8;
}*/
.form_for_btn_new {
  width: 870px;
  height: 40px;
  margin-bottom: 5px;
}

.container_for_event_forms {
  width: 100%;
  padding: 0 0 15px 10px;
  /* border: 1px solid red; */
  display: grid;
  align-content: start;
  grid-template-columns: repeat(2, 1fr);
}


@media (max-width: 992px) {
  .back {
    overflow-y: auto;
    overflow-x: hidden;
  }

  .container_for_event_forms {

    grid-template-columns: repeat(1, 1fr);
  }

  .profileNavbar {
    gap: 20px;
    font-size: 14px;
  }

}

@media (max-width: 768px) {
  .back {
    overflow-y: auto;
    overflow-x: hidden;
  }

  .info {
    top: 0;
    left: 0;
    width: 100%;
    height: 30%;
    display: flex;
    flex-direction: row;
    gap: 5px;
  }

  .body {
    top: 30%;
    left: 0;
    width: 100%;
    height: 70%;
  }

  .ellipse_nav_logo {
    width: 130px;
    height: 130px;
    padding-bottom: 0;
  }

  .profile_nickname {
    margin-left: 0;
    /* border: 1px solid red; */
    top: 20%;
    font-size: 20px;
  }

  .first_hr {
    display: none;
  }

  .user_info {
    /* border: 1px solid red; */
    margin-top: 0;
    gap: 25px;
    display: flex;
    flex-direction: column;
    align-items: flex-start;
  }

  .user_description {
    margin-top: 0;
    padding: 5px;
    color: #858585;
    /* border: 1px solid red; */
    font-size: 14px;
    flex: 1;
  }

  .your_subscribers,
  .profile_info_users_events,
  .subscriptions {
    display: flex;
    gap: 5px;
    flex-direction: row;
  }

}
</style>
