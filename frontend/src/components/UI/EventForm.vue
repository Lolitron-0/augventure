<template>
<!--  -->
  <router-link style="text-decoration: none" :to="{ name: 'voting', params: {id: this.id} }">
    <div class="event_form" id="event-form">
      <div class="body_event" id="body_event">
        <div class="title_event" id="title-event">{{ this.title }}</div>
        <div class="description_event" id="description_event">{{ this.description }}</div>
        <div class="content_event" id="content_event">
          <div class="content_art" id="content_art">art</div>
          <div class="content_boobs" id="content_boobs">hello</div>
          <div class="content_tag" id="content_tag">long long tag</div>
        </div>
        <div class="stars_event" id="stars_event">
          <i class='bx bxs-star'></i>
          {{ this.likes }}
        </div>
      </div>
      <div class="state_event" id="state_event">
        {{ this.state }}
      </div>
    </div>
  </router-link>
</template>

<script>
export default {
  props: ['title', 'description', 'state', 'likes', 'id'],

}
</script>

<style scoped>
@import "@/styles.css";

.event_form {
  color: var(--text-wight-color);
  display: flex;
  justify-content: space-between;
  width: 95%;
  height: 130px;
  margin: 5px;
  border: .4px solid var(--border-light-gray-color);
  border-radius: 5px;
  padding: 5px;
  gap: 5px;
}
.state_event{
  display: flex;
  flex-direction: column;
  width: 30%;
  /* border: 1px solid green; */
  font-size: 16px;
  justify-content: center;
  align-items: center;

}
.body_event{
  /* border: 1px solid green; */
  width: 70%;
  font-size: 14px;
  align-items: center;
  padding: 5px;
}
.content_event{
  display: flex;
  justify-content: left;
  gap: 10px;
  color: var(--content-event);
  padding-bottom: 10px;
}
.title_event{
  color: var(--title-event-color);
  font-size: 16px;
  padding-bottom: 10px;
}
.description_event{
  color: var(--description-event);
  padding-bottom: 10px;
}
.stars_event{
  display: flex;
  gap: 5px;
  padding-bottom: 10px;
  font-size: 16px;
}
.content_art, .content_boobs, .content_tag{
  border: 1px solid var(--border-light-gray-color);
  border-radius: 10px;
  padding: 2px 7px;
}

@media (max-width: 1300px) {
  .title_event{
    font-size: 14px;
  }
  .state_event{
    font-size: 14px;
  }
  .content_event{
    font-size: 12px;
  }
  .description_event{
    font-size: 14px;
  }
  .stars_event{
    font-size: 14px;
  }
}

@media (max-width: 1150px) {
  .state_event{
    width: 27%;

  }
  .body_event{
    width: 73%;
  }
  .state_event{
    font-size: 12px;
  }
}
@media (max-width: 992px) {
  .state_event{
    width: 40%;
  }
  .body_event{
    width: 60%;
  }
  .state_event{
    font-size: 18px;
  }
  .title_event{
    font-size: 18px;
  }
  .content_event{
    font-size: 16px;
  }
  .description_event{
    font-size: 16px;
  }
  .stars_event{
    font-size: 18px;
  }

}
@media (max-width: 768px) {
  .event_form{
    width: 98%;
  }
  hr{
    display: none;
  }
}
@media (max-width: 430px) {
  .event_form{
    width: 98%;
  }
}
</style>