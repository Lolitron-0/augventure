<template>
  <div class="eventNavbar">
    <div class="newEvent">
      <router-link :to="{name: 'newEvents', params: {name: 'newEvents'}}"
                   class="rout_event_nav_text"
      >
        <my-button :class="{ 'active': isNewEventActive, 'btn_event': !isNewEventActive}">New Events</my-button>
      </router-link>
    </div>
    <div class="currentEvent">
      <router-link :to="{name: 'currentEvents', params: {name: 'currentEvents'}}"
                   class="rout_event_nav_text"
      >
        <my-button :class="{ 'active': isCurrentEventActive, 'btn_event': !isCurrentEventActive}">Current Events</my-button>
      </router-link>
    </div>
  </div>
</template>

<script>
import MyButton from "@/components/UI/MyButton.vue";

export default {
  components: {MyButton},
  computed: {
    isCurrentEventActive() {
      return this.$route.name === 'currentEvents';
    },
    isNewEventActive() {
      return this.$route.name === 'newEvents';
    }
  }
}
</script>

<style scoped>
.eventNavbar{
  //border: 1px solid red;
  width: 100%;
  display: flex;
  justify-content: center;
  gap: 200px;
}

.btn_event{
  width: 200px;
  height: 35px;
  border: none;
  justify-content: center;
  align-items: center;
  color: #cfcfcf;
}

.rout_event_nav_text{
  text-decoration: none;
  color: #cfcfcf;
}

.active{
  width: 200px;
  height: 35px;
  border: none;
  justify-content: center;
  align-items: center;
  color: #cfcfcf;
  background-color: #31a0a8;
}

@media (max-width: 992px) {
  .eventNavbar{
    gap: 100px;
  }
}
@media (max-width: 768px) {
  .btn_event, .active {
    width: 170px;
    height: 30px;
  }
}

</style>