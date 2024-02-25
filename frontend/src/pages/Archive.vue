<template>
  <div class="back">
    <div class="archive">
      <info-block-for-profile :nickname="user.username" :bio="user.bio" :photo="user.pfp_url" />
      <div class="body">
        <profile-navbar class="profileNavbar"></profile-navbar>
        <div class="form_for_btn_new">
          <router-link :to="{ name: 'newEvents' }">
            <button class="btn_new">New</button>
          </router-link>
        </div>
        <div class="container_for_event_forms">
          <event-form v-for="(event, index) in events" :key="index" :title="event.title" :description="event.description"
                      :state="event.state" :likes="event.likes" />
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import ProfileNavbar from "@/components/UI/ProfileNavbar.vue";
import InfoBlockForProfile from "@/components/InfoBlockForProfile.vue";
import EventForm from "@/components/UI/EventForm.vue";
import MyButton from "@/components/UI/MyButton.vue";

export default {
  components: { InfoBlockForProfile, EventForm, ProfileNavbar,  },

  data() {
    const user = JSON.parse(localStorage.getItem('user'));
    return {
      user: user,
      events: [],
    }
  },
  async beforeMount() {
    try {
      const events = await this.$api.events.filterEvents({
        "filter": [ // or array
          [ // and array
            ["state", "=", "ended"],
            ["author_id", "=", this.user.id]
          ]
        ]
      });
      console.log(events);
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
    } catch (error) {
      console.log('failed:', error);
    }
  }


}
</script>

<style scoped>
@import "@/styles.css";

.back {
  background-color: var(--background-app-color);
  position: fixed;
  width: 100vw;
  max-height: 100vh;
  height: 100vh;
  padding: 80px 5% 24px 5%;
  overflow-y: auto;
  overflow-x: hidden;

}

.archive {
  position: absolute;
//border: 1px solid red;
  width: 85vw;
  height: 80vh;
}
.info{
  position: absolute;
  top: 0;
  left: 0;
//border: 1px solid #31a0a8;
  width: 25%;
  height: 80vh;
  padding: 2%;
}
.body{
  position: absolute;
  top: 0;
  left: 25%;
//border: 1px solid #cfcfcf;
  width: 75%;
  height: 80vh;
  padding: 0 10px 10px 10px;
}

.ellipse_nav_logo {
  width: 90%;
  height: 0;
  padding-bottom: 90%;
  max-width: 256px;
  max-height: 256px;
  border: solid 1px #858585;
  box-sizing: border-box;
  background-color: #0e73bd;
  cursor: pointer;
  border-radius: 50%;
}

.profile_nickname{
  margin-top: 10px;
  color: #0e73bd;
//border: 1px solid red;
  font-size: 22px;
}
</style>